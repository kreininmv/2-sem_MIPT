#include "hash_func.h"

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
  return number << 1 | ((number & (1 << (sizeof(number) - 1))) >> (sizeof(number) - 1));
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
  int iters = str->len / 4;
  for (int i = 0; i < iters; i++) {
    hash += (unsigned char)str->str[i];
    hash -= (hash << 13) | (hash >> 19);
    hash += (unsigned char)str->str[i + 1];
    hash -= (hash << 13) | (hash >> 19);
    hash += (unsigned char)str->str[i + 2];
    hash -= (hash << 13) | (hash >> 19);
    hash += (unsigned char)str->str[i + 3];
    hash -= (hash << 13) | (hash >> 19);
  }

  return hash;
}

unsigned long magic_num = 0xFFFFFFFFUL;

hash_type crc32(const mk5::line* str) {
  
  char* string = str->str;
  magic_num = 0xFFFFFFFFUL;
  size_t len = str->len / sizeof(uint32_t);

  for (size_t i = 0; i < len; ++i) {
    magic_num = _mm_crc32_u32(magic_num, *(const uint32_t*)string);
    string += sizeof(uint32_t);
  }

  return magic_num;
}

hash_type aqua_hash(const mk5::line* str) {
  hash_type hash = 0;
  char* cur_str = str->str;
  __m128i magic_num = _mm_set1_epi32(0xDEADBEEF);
  __m128i hash_32 = { *cur_str, *(cur_str + 1), *(cur_str + 2), *(cur_str + 3) };
  __m128i final_hash_32 = _mm_set1_epi32(0);
  int len = str->len / sizeof(uint32_t);

  for (int i = 0; i < len; i++) {
    hash_32 = { *(cur_str + 4*i), *(cur_str + 1 + 4 * i), *(cur_str + 2 + 4 * i), *(cur_str + 3 + 4 * i) };
    final_hash_32 = _mm_add_epi32(_mm_aesenc_si128(hash_32, magic_num), final_hash_32);
    
  }

  return (*((int32_t*)&final_hash_32 + 0)) + (*((int32_t*)&final_hash_32 + 1)) + (*((int32_t*)&final_hash_32 + 2)) + (*((int32_t*)&final_hash_32 + 3));
}
