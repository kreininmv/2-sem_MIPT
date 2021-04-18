#ifndef  _HASH_FUNC_H
#define  _HASH_FUNC_H

#include <immintrin.h>
#include <xmmintrin.h>
#include <nmmintrin.h>
#include "line.h"
#include "hash_table.h"

hash_type best_hash(const mk5::line* str);

hash_type first_sym_hash(const mk5::line* str);

hash_type len_hash(const mk5::line* str);

hash_type sum_hash(const mk5::line* str);

hash_type worst_hash(const mk5::line* str);

hash_type ly_hash(const mk5::line* str);

hash_type rot_13(const mk5::line* str);

hash_type aqua_hash(const mk5::line* str);

hash_type crc32(const mk5::line* str);
#endif
