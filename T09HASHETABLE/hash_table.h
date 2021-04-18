#ifndef  _HASH_TABLE_H
#define  _HASH_TABLE_H

#include "line.h"
#include "list.h"

//Type for hash
typedef unsigned long long hash_type;

const size_t table_size = 0x1e;

namespace mk5 {
  
  class hash_table {
  private:
    list<const line *> table[table_size];
    
    hash_type (*func_hash)(const line* str);
    char* buf = nullptr;
    line* strs = nullptr;
    size_t buf_size = 0, strs_size = 0;
    
    bool is_header_print = FALSE;

  public:

    // default constructor
    hash_table(void) : 
      buf(nullptr),
      buf_size(0),
      strs_size(0),
      strs(nullptr),
      is_header_print(false)
    {
      func_hash = nullptr;
    }

    // constructor
    hash_table(hash_type(*func)(const line* s)) : 
      buf(nullptr),
      buf_size(0),
      strs_size(0),
      strs(nullptr),
      is_header_print(false)
    {
      func_hash = func;
    }
    
    bool load_txt(const char filename[]);
    
    void hashing(hash_type(*Hash)(const line* str), bool IsDic = true);
    
    bool put_to_csv(const char file_out[], char sep_sym, const char name[]);
    
    bool insert(const line* str, bool IsDic = true);
    
    hash_type find(const line* str, hash_type hsh /*= 0 */);
    
    bool table_ok(void);

    ~hash_table(void)
    {
      if (buf != nullptr)
        free(buf);
      if (strs != nullptr)
        delete[] strs;
    }

      void clear(void);
  private:
    
      void print_csv_header(FILE* f, char sep_sym);
  };
}

#endif 