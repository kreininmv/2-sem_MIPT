#include "line.h"
#include "list.h"
#include "hash_table.h"
#include "hash_func.h"

const int MAX_NAME = 100;

int main(void) {
  
  mk5::hash_table table;

  mk5::hash_table tbl(best_hash);
  const int size_func = 7;
  char FileName[MAX_NAME] = {};


  const char* names[size_func] = {
      "best_hash;"     ,  
      "first_sym_hash;",
      "len_hash;"      ,
      "sum_hash;"      ,
      "worst_hash;"    ,
      "ly_hash;"       ,
      "rot_13;"
  };


  hash_type(*hash[size_func])(const mk5::line * str) = {
    best_hash     ,
    first_sym_hash,
    len_hash      ,
    sum_hash      ,
    worst_hash    ,
    ly_hash       ,
    rot_13

  };

  std::cout << "It's a hash table program\n" << "Input file name to start: ";
  std::cin >> FileName;

  if (!tbl.load_txt(FileName))
    return 1;

  std::cout << "Input file name to svae: ";
  std::cin >> FileName;
  
  for (int i = 0; i < size_func; i++)
  {
    tbl.hashing(hash[i]);
    tbl.put_to_csv(FileName, ';', names[i]);
    tbl.clear();
  }

  return 0;
}