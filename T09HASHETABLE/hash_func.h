#ifndef  _HASH_FUNC_H
#define  _HASH_FUNC_H

#include "line.h"
#include "hash_table.h"

hash_type best_hash(const mk5::line* str) {
  return 1;
}

hash_type first_sym_hash(const mk5::line* str) {
  return str->str[0];
}

hash_type len_hash(const mk5::line* str) {
  return str->len;
}

hash_type sum_hash(const mk5::line* str) {
  hash_type sum = 0;
  for (int i = 0; i < str->len; i++)
    sum += str->str[i];
  
  return sum;
}

template<typename data_type>
data_type Rol(data_type number) {
  return number << 1 | ((number & (1 << (sizeof(number) - 1))) >> (sizeof(number)-1));
}

hash_type worst_hash(const mk5::line* str) {
  hash_type hash = 0;
  for (int i = 0; i < str->len; i++)
    hash = Rol(hash) ^ str->str[i];

  return hash;
}

hash_type ly_hash(const mk5::line* str) {
  hash_type hash = 0;

  for (int i = 0; i < str->len; i++)
    hash = (hash * 1664525) + (unsigned char)(str->str[i]) + 1013904223;

  return hash;
}

hash_type rot_13(const mk5::line* str) {
  hash_type hash = 0;

  for (int i = 0; i < str->len; i++) {
    hash += (unsigned char)str->str[i];
    hash -= (hash << 13) | (hash >> 19);
  }

  return hash;
}
#endif
