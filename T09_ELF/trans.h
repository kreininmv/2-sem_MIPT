#ifndef __TRANS__
#define __TRANS__

#include "line.h"
//#include "PROCESSOR/T03PROC/PROC.h"
#include "commands.h"
#include "buffer.h"


const size_t jmp_size = 1000;

const size_t CODE_CHAR = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;
const size_t DATA_CHAR = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA;
const size_t IDATA_CHAR = IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ;
const size_t IMAGE_BASE = 0x00400000;
const size_t ENTRY_POINT_ADDR = 0x1000;
const size_t VRT_SIZE = 0x5000;
const size_t SIZE_RAW = 0x1000;
const size_t DATA_START = 2*VRT_SIZE + ENTRY_POINT_ADDR;
const size_t IMPORT_START = VRT_SIZE  + ENTRY_POINT_ADDR;

bool translate(const mk5::buffer& in, mk5::buffer& out);
void fill_jump_table(const mk5::buffer& in);
bool create_exe(const char filename[], const mk5::buffer& out);

IMAGE_NT_HEADERS create_nt_header(int num_of_sec);
IMAGE_FILE_HEADER create_file_header(int num_of_sec);
IMAGE_OPTIONAL_HEADER create_opt_header(void);
IMAGE_SECTION_HEADER create_sec_header(const char sec_name[], size_t vrt_size, 
                                       size_t vrt_addr, size_t size_raw_data, 
                                       size_t ptr_raw_data, size_t charac);

bool simplify(const mk5::buffer& in);

namespace mk5 {
  struct import_name {
    WORD hint;
    const char* name;
    size_t size;
    import_name(const char Name[], size_t Size, WORD Hint = 0) : hint(Hint), name(Name), size(Size)
    {};

    void fill(const char Name[], size_t Size, WORD Hint = 0) {
      name = Name;
      size = Size;
      hint = Hint;
    }

    size_t put_in_file(FILE* file) {
      if (file == nullptr)
        return 0;

      fwrite(&hint, sizeof(WORD), 1, file);
      fwrite(name, sizeof(char), size, file);
      char zero = 0;
      fwrite(&zero, sizeof(zero), 1, file);

      return size;
    }
  };

  class import_table {
  private:
    size_t                   size;
    IMAGE_IMPORT_DESCRIPTOR  *table;
    import_name              *name_imp;
    size_t                   names_size;
    IMAGE_THUNK_DATA64       *thunk;
    size_t                   align_size;

  public:
    import_table(size_t Size = 5) : size(Size + 1), name_imp(nullptr), names_size(0), align_size(0)
    {
      table = (IMAGE_IMPORT_DESCRIPTOR*)calloc(Size + 1, sizeof(IMAGE_IMPORT_DESCRIPTOR));
      name_imp = (import_name*)calloc(Size, sizeof(import_name));
      thunk = (IMAGE_THUNK_DATA64*)calloc(Size, sizeof(thunk[0]));
      fill_default(); 
    }

    bool fill_default(void) {
      
      fill_def_names();

      size_t tbl_size = sizeof(table[1]) * size;
      size_t thunks_size = sizeof(thunk[1]) * (size - 1);
      size_t names_start = IMPORT_START + tbl_size + thunks_size;
      size_t fst_thunk_start = names_start + names_size;
      size_t name_rva = fst_thunk_start + thunks_size;
      size_t cur_name_size = 0;

      for (size_t i = 0; i < size - 1; ++i) {
        table[i].OriginalFirstThunk = IMPORT_START + tbl_size + i * sizeof(thunk[1]);
        table[i].FirstThunk         = fst_thunk_start + i * sizeof(thunk[1]);
        table[i].Name               = name_rva;
        thunk[i].u1.AddressOfData   = (names_start + cur_name_size);
        cur_name_size              += name_imp[i].size + 1 + 2;
      }

      return true;
    }

    void fill_def_names(void) {
      name_imp[0].fill("ExitProcess", 11);
      name_imp[1].fill("WriteConsoleA", 13);
      name_imp[2].fill("ReadConsoleA", 12);
      name_imp[3].fill("ToDec", 5);
      name_imp[4].fill("mk5scanf", 8);


      for (size_t i = 0; i < size - 1; ++i)
        names_size += name_imp[i].size + 1 + 2;
    }

    bool put_in_file(FILE* file){
      if (file == nullptr)
        return false;

      const size_t dll_name_size = 11;
      const size_t stub_size = 1 + SIZE_RAW - (sizeof(table[0]) * size + 2 * sizeof(thunk[1]) * (size - 1) + names_size + dll_name_size);
      char* stub = new char[stub_size] {0};

      fwrite(table, sizeof(table[0]), size, file);
      fwrite(thunk, sizeof(thunk[0]), size - 1, file);

      for (size_t i = 0; i < size - 1; ++i)
        name_imp[i].put_in_file(file);

      fwrite(thunk, sizeof(thunk[0]), size - 1, file);

      fprintf(file, "mk5lib.dll\0");

      fwrite(stub, sizeof(stub[0]), stub_size, file);

      delete[] stub;
      return true;
    }

    unsigned GetProcAddr(size_t num)
    {
      return sizeof(table[0]) * size + sizeof(thunk[0]) * (size - 1) + names_size + num * sizeof(thunk[0]);
    }

    ~import_table(void)
    {
      if (table != nullptr)
      {
        free(table);
        table = nullptr;
      }
      if (name_imp != nullptr)
      {
        free(name_imp);
        name_imp = nullptr;
      }
      if (thunk != nullptr)
      {
          free(thunk);
        thunk = nullptr;
      }
      size = 0;
    }
  };
}

extern mk5::import_table IMPORT_TABLE;

struct jump_inf {
  unsigned char* my_asm_ptr;
  unsigned char* x86_ptr;
  unsigned char* my_asm_dest;
  unsigned char* x86_dest;
};

struct jump_table {
  jump_inf table[jmp_size];
  size_t size;
  jump_table(void);

  int jump_process(unsigned char* my_asm_ptr, unsigned char* x86_ptr);
  
  bool cmd_process(unsigned char* my_asm_addr, unsigned char* x86_addr, bool is_jump = false);
  
  bool push_old_inf(unsigned char* my_asm_ptr, unsigned char* my_asm_dest);
};

const IMAGE_DOS_HEADER DOS_HEADER = { 
  .e_magic = 'ZM', .e_cblp = 0x0090, 
  .e_cp = 0x0003, .e_cparhdr = 0x0004, 
  .e_minalloc = 16, .e_maxalloc = 0xFFFF, 
  .e_sp = 0x00B8, .e_lfarlc = 0x0040, 
  .e_lfanew = 0x00B0 
};

const unsigned char DOS_STUB[] = {
  0x0E,	0x1F, 0xBA, 0x0E,
  0x00, 0xB4, 0x09, 0xCD,
  0x21, 0xB8, 0x01, 0x4C,
  0xCD, 0x21, 0x54, 0x68,
  0x69, 0x73, 0x20, 0x70,
  0x72,	0x6F, 0x67, 0x72,
  0x61, 0x6D, 0x20, 0x63,
  0x61, 0x6E, 0x6E, 0x6F,
  0x74, 0x20, 0x62, 0x65,
  0x20, 0x72, 0x75, 0x6E,
  0x20,	0x69, 0x6E, 0x20,
  0x44,	0x4F, 0x53, 0x20,
  0x6D,	0x6F, 0x64, 0x65,
  0x2E,	0x0D, 0x0D, 0x0A,
  0x24,	0x00, 0x00, 0x00,
  0x00,	0x00, 0x00, 0x00,
  0x5D,	0x5C, 0x6D, 0xC1,
  0x19,	0x3D, 0x03, 0x92,
  0x19,	0x3D, 0x03, 0x92,
  0x19,	0x3D, 0x03, 0x92,
  0x97,	0x22, 0x10, 0x92,
  0x1E,	0x3D, 0x03, 0x92,
  0xE5,	0x1D, 0x11, 0x92,
  0x18,	0x3D, 0x03, 0x92,
  0x52,	0x69, 0x63, 0x68,
  0x19, 0x3D, 0x03, 0x92,
  0x00, 0x00, 0x00, 0x00,
  0x00,	0x00, 0x00, 0x00
};

#endif