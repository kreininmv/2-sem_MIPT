#include "line.h"
#include "list.h"
#include "hash_table.h"
#include "hash_func.h"

const int MAX_NAME = 100;

int main(void) {
  
  mk5::hash_table table;

  mk5::hash_table tbl(best_hash);
  const int size_func = 9;


  const char* names[size_func] = {
      "best_hash;"     ,  
      "first_sym_hash;",
      "len_hash;"      ,
      "sum_hash;"      ,
      "worst_hash;"    ,
      "ly_hash;"       ,
      "rot_13;"        ,
      "aqua_hash"      ,
      "crc32"
  };


  hash_type(*hash[size_func])(const mk5::line * str) = {
    best_hash     ,
    first_sym_hash,
    len_hash      ,
    sum_hash      ,
    worst_hash    ,
    ly_hash       ,
    rot_13        ,
    aqua_hash     ,
    crc32

  };

  //char FileName[MAX_NAME] = {};
  //std::cout << "It's a hash table program\n" << "Input file name to start: ";
  //
  //std::cin >> FileName;
  //
  if (!tbl.load_txt("dict.dic"))
    return 1;
  //
  //std::cout << "Input file name to svae: ";
  //std::cin >> FileName;
   int j = 0;
   tbl.hashing(hash[size_func - 3]);
   for (; j < tbl.strs_size; j++) {
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
     tbl.find(&tbl.strs[j]);
  }


  //for (int i = 0; i < size_func; i++)
  //{
  //  tbl.hashing(hash[i]);
  //  
  //  for (int j = 0; j < tbl.strs_size; j++)
  //    tbl.find(&tbl.strs[j]);
  //
  //  tbl.clear();
  //}
  

  // 2 - 33
  // 3 - 32
  // 4 - 29


  // rot13 - 80; insert - 20
  // rot13 - 69; insert - 31
  return 0;
}