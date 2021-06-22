#include "trans.h"

jump_table TABLE;
mk5::import_table IMPORT_TABLE;

bool translate(const mk5::buffer& in, mk5::buffer& out) {
  const unsigned char* code_ptr = (unsigned char*)((int*)in.buf + 4);
  unsigned char* buf_out = (unsigned char *)out.buf;
  
  fill_jump_table(in);

  bool IsJmp = false; 
  //push 1, push 2, push 4, hlt
  //header - 16 + 4 + 3 * 4 = 32
    for (size_t PC = 0; PC < in.size - 16;) {
#define DEF_INSTR(name, code, translator, table_act)                               \
  case code:                                                                       \
    IsJmp = (code >= 17 && code <= 24);                                            \
    TABLE.cmd_process(const_cast<unsigned char *>(&code_ptr[PC]), buf_out, IsJmp); \
    ++PC;                                                                          \
    {translator}                                                                   \
    printf("%s\n", #name);                                                         \
    break;


#define DEF_INSTRARG(name, reg, code, translator, table_act)                       \
  case code:                                                                       \
    IsJmp = (code >= 17 && code <= 24);                                            \
    TABLE.cmd_process(const_cast<unsigned char *>(&code_ptr[PC]), buf_out, IsJmp); \
    ++PC;                                                                          \
    {translator}                                                                   \
    printf("%s\n", #name);                                                         \
    break;

    switch ((unsigned char)code_ptr[PC]) {
    
    #include "instruction.h"

    default:
      printf("What a fuck wrong with you? I don't know this code: %X\nposition in file: %d\n", code_ptr[PC], PC);
      return false;
    }
  }
#undef DEF_INSTR
#undef DEF_INSTRARG
  return true;
}

void fill_jump_table(const mk5::buffer& in) {
  unsigned char* code_ptr = (unsigned char *)((int *)in.buf + 4);

  for (size_t PC = 0; PC < in.size - 16;) {
#define DEF_INSTR(name, code, translate, tbl_act)    \
  case code:                                         \
    ++PC;                                            \
    {tbl_act;}                                       \
    printf("%s\n", #name);                           \
    break;                                        

#define DEF_INSTRARG(name, reg, code, translate, tbl_act) \
  case code:                                              \
    ++PC;                                                 \
    {tbl_act;}                                            \
    printf("%s\n", #name);                                \
    break;                                        

    switch ((unsigned char)code_ptr[PC]) {
      #include "instruction.h"
    default:
      printf("What a fuck wrong with you? I don't know this code: %X\nposition in file: %d\n", code_ptr[PC], PC);
      return;
    }
    //дефайны для определения меток и джампов
  }
}
#undef DEF_INSTRARG
#undef DEF_INSTR
jump_table::jump_table(void) : table{ 0 }, size(0)
{}

bool jump_table::push_old_inf(unsigned char* my_asm_ptr, unsigned char* my_asm_dest) {
  assert(size < jmp_size);

  table[size].my_asm_ptr = my_asm_ptr;
  table[size].my_asm_dest = my_asm_dest;
  
  size++;

  return true;
}

bool jump_table::cmd_process(unsigned char* my_asm_addr, unsigned char* x86_addr, bool is_jump) {
  for (size_t i = 0; i < size; i++) {
    if (table[i].my_asm_dest == my_asm_addr) {
      if (table[i].x86_ptr != nullptr) {
        int rel_x86_dest = static_cast<int>(x86_addr - table[i].x86_ptr - sizeof(int) - sizeof(char));
        *(reinterpret_cast<int*>(table[i].x86_ptr + 1)) = rel_x86_dest;
      }
      table[i].x86_dest = x86_addr;
    }
    else if (is_jump && table[i].my_asm_ptr == my_asm_addr) {
      unsigned char jump_code = *(table[i].my_asm_ptr);
      unsigned char* x86_cond_addr = x86_addr;

      if (jump_code != 24 && jump_code != 17)
        x86_cond_addr += 5; //pop, pop, cmp, half of cond jump code

      table[i].x86_ptr = x86_cond_addr;
      *reinterpret_cast<int*>(x86_cond_addr + 1) = static_cast<int>(table[i].x86_dest - table[i].x86_ptr - sizeof(int) - sizeof(char));
  
      is_jump = false;
    }
  }

  return true;
}

int jump_table::jump_process(unsigned char* my_asm_ptr, unsigned char* x86_ptr) {
  for (size_t i = 0; i < size; ++i) {
    if (table[i].my_asm_dest == my_asm_ptr)
    {
    }
    else if (table[i].my_asm_ptr == my_asm_ptr) {
      table[i].x86_ptr = x86_ptr;
      *reinterpret_cast<int*>(x86_ptr + 1) = static_cast<int>(table[i].x86_dest - table[i].x86_ptr - sizeof(char) - sizeof(int));
      return (int)i;
    }
  }
  return -1;
}

bool create_exe(const char filename[], const mk5::buffer& out) {
  const size_t stub_size = SIZE_RAW;
  char stub[stub_size] = {0};

  FILE* exe = fopen(filename, "wb");
  size_t vrt_addr = ENTRY_POINT_ADDR,
    vrt_size = VRT_SIZE,
    size_raw = SIZE_RAW,
    ptr_raw = 0x400;

  if (exe == nullptr) {
    printf("I can't open %s file", filename);
    return false;
  }

  //dos header
  fwrite(&DOS_HEADER, sizeof(DOS_HEADER), sizeof(char), exe);
  //dost stub
  fwrite(&DOS_STUB, sizeof(DOS_STUB[0]), sizeof(DOS_STUB) / sizeof(DOS_STUB[0]), exe);
  //optional header and data directories
  IMAGE_NT_HEADERS *NT_HEADER = new IMAGE_NT_HEADERS;
  *NT_HEADER = create_nt_header(3);
  fwrite(NT_HEADER, sizeof(IMAGE_NT_HEADERS), 1, exe);
  
  //sections table
  //code
  IMAGE_SECTION_HEADER* TEXT_SECTION = new IMAGE_SECTION_HEADER;
  *TEXT_SECTION = create_sec_header(".text", vrt_size, vrt_addr, size_raw, ptr_raw, CODE_CHAR);
  fwrite(TEXT_SECTION, sizeof(IMAGE_SECTION_HEADER), 1, exe);
  //idata
  IMAGE_SECTION_HEADER* IDATA_SECTION = new IMAGE_SECTION_HEADER;
  *IDATA_SECTION = create_sec_header(".idata", vrt_size, IMPORT_START, size_raw, ptr_raw + size_raw, IDATA_CHAR);
  fwrite(IDATA_SECTION, sizeof(IMAGE_SECTION_HEADER), 1, exe);
  //data
  IMAGE_SECTION_HEADER* DATA_SECTION = new IMAGE_SECTION_HEADER;
  *DATA_SECTION = create_sec_header(".data", vrt_size, DATA_START, size_raw, ptr_raw + 2 * size_raw, DATA_CHAR);
  fwrite(DATA_SECTION, sizeof(IMAGE_SECTION_HEADER), 1, exe);
  
  

  size_t size_zero = 0x400 - (sizeof(DOS_HEADER) + sizeof(DOS_STUB) + sizeof(IMAGE_SECTION_HEADER) * 3 + sizeof(IMAGE_NT_HEADERS));
  char* zero = new char[0x1000]{ 0 }; 
  
  //Выравнивание нулями до размера sections table, указанного в optional headere
  //480 ноликов пушу
  fwrite(zero, sizeof(char), size_zero, exe);
  fwrite(out.buf, sizeof(out.buf[0]), out.size, exe);
  //printf("%d", sizeof(DOS_HEADER) + sizeof(DOS_STUB) + sizeof(IMAGE_SECTION_HEADER) * 3 + sizeof(IMAGE_NT_HEADERS));
  
  //code, размер ук
   //code
  printf("Offset from beggining - %x", sizeof(DOS_HEADER) + sizeof(DOS_STUB) + sizeof(IMAGE_SECTION_HEADER) * 3 + sizeof(IMAGE_NT_HEADERS));
  

  //idata
  IMPORT_TABLE.put_in_file(exe);
  //data
  fwrite(zero, sizeof(char), 0x1000, exe);
  

  fclose(exe);
  delete[] zero;
  delete DATA_SECTION;
  delete IDATA_SECTION;
  delete TEXT_SECTION;
  delete NT_HEADER;

  return true;
}

IMAGE_FILE_HEADER create_file_header(int num_of_sec) {
  IMAGE_FILE_HEADER FILE_HDR = {

    .Machine = IMAGE_FILE_MACHINE_I386,
    .NumberOfSections = static_cast<WORD>(num_of_sec),
    .TimeDateStamp = static_cast<DWORD>(time(nullptr)),
    .SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER32),
    .Characteristics = IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_32BIT_MACHINE
  };
  return FILE_HDR;
}

IMAGE_OPTIONAL_HEADER create_opt_header(void) {
  IMAGE_OPTIONAL_HEADER OPT_HDR = {
    .Magic = IMAGE_NT_OPTIONAL_HDR32_MAGIC,
    .AddressOfEntryPoint = ENTRY_POINT_ADDR,
    .ImageBase = IMAGE_BASE,
    .SectionAlignment = ENTRY_POINT_ADDR,
    .FileAlignment = 0x200,
    .MajorSubsystemVersion = 4,
    .SizeOfImage = 2 * 0x8000, 
    .SizeOfHeaders = 0x400,
    .Subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI,
    .NumberOfRvaAndSizes = 0x10    
  };
  OPT_HDR.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = IMPORT_START;// +0x1000;
  //OPT_HDR.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = 

  return OPT_HDR;
}

IMAGE_SECTION_HEADER create_sec_header(const char sec_name[], size_t vrt_size, size_t vrt_addr, size_t size_raw_data, size_t ptr_raw_data, size_t charac) {
  IMAGE_SECTION_HEADER SEC_HDR = {
    .VirtualAddress = vrt_addr,
    .SizeOfRawData = size_raw_data,
    .PointerToRawData = ptr_raw_data,
    .Characteristics = charac
  };
  sprintf_s((char* const)SEC_HDR.Name, (size_t)IMAGE_SIZEOF_SHORT_NAME, "%s", sec_name);
  SEC_HDR.Misc.VirtualSize = vrt_size;

  return SEC_HDR;
}

IMAGE_NT_HEADERS create_nt_header(int num_of_sec) {
  IMAGE_NT_HEADERS PE_HEADER = {
    .Signature = '\0EP\0',
    .FileHeader = create_file_header(num_of_sec),
    .OptionalHeader = create_opt_header()
  };
  return PE_HEADER;
}