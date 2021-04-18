#include "hash_table.h"

#define TABLE_ASSERT 
//#define TABLE_ASSERT assert(table_ok())

void mk5::hash_table::clear(void)
{
  for (int i = 0; i < table_size; i++)
    table[i].clear();
} 

mk5::line* put_points_to_strings(char *buf, size_t buf_size, int count_of_strings)
{
  mk5::line* lines = new mk5::line[count_of_strings];
  int cur_sym = 0, past_cur_sym = 0;
  int i_sym = 0;
  for (i_sym = 0; i_sym < count_of_strings - 1; i_sym++)
  {
    lines[i_sym].str = &(buf[cur_sym]);
    past_cur_sym = cur_sym;
    while (buf[cur_sym] != '\r')
      cur_sym++;

    buf[cur_sym] = '\n';
    buf[cur_sym + 1] = 0;
    cur_sym += 2;
    lines[i_sym].len = cur_sym - past_cur_sym;
  }

  /* Last string */
  lines[count_of_strings - 1].str = &(buf[cur_sym]);
  past_cur_sym = cur_sym;
  while (buf[cur_sym] != 0)
    cur_sym++;
  lines[count_of_strings - 1].len = cur_sym + 1 - past_cur_sym;

  return lines;
}


char *read_buf(const char FileName[], size_t &buf_size)
{
  FILE* file = fopen(FileName, "rb");

  if (file == NULL)
  {
    printf("We can't find the file...\n");
    return 0;
  }
  fseek(file, 0, SEEK_END);
  buf_size = ftell(file) + 1;

  rewind(file);

  char* buf = (char*)calloc(buf_size, sizeof(char));
  fread(buf, sizeof(char), buf_size - 1, file);

  fclose(file);

  buf[buf_size - 1] = 0;

  return buf;
}

int count_symbols(char *buf, char sym) {
  int count_of_sym = 0, i_sym = 0;

  while (buf[i_sym++] != 0)
    if (buf[i_sym] == sym)
      count_of_sym++;

  return count_of_sym;
}

bool mk5::hash_table::load_txt(const char filename[])
{
  assert(filename != nullptr);
  TABLE_ASSERT;

  buf = read_buf(filename, buf_size);
  if (buf == nullptr)
    return false;
  strs_size = count_symbols(buf, '\n') + 1;
  strs = put_points_to_strings(buf, buf_size, strs_size);
  if (strs == nullptr)
  {
    printf("Error in creating strings.\n");
    return false;
  }
  TABLE_ASSERT;
  return true;
} 

bool mk5::hash_table::insert(const line* str, bool IsDic )
{
  TABLE_ASSERT;
  hash_type h = func_hash(str);

  try
  {
    if (IsDic || find(str, h) == 0)
      table[h % table_size].push_back(str);
  }
  catch (...)
  {
    printf("Error in list\n");
    return false;
  }
  TABLE_ASSERT;
  return true;
} 

hash_type mk5::hash_table::find(const line* str, hash_type hsh = 0)
{
  TABLE_ASSERT;
  if (hsh)
    hsh = func_hash(str);
  
  if (table[hsh % table_size].get_index(str) == -1)
    return 0;

  TABLE_ASSERT;
  return hsh;
} 

void mk5::hash_table::hashing(hash_type(*Hash)(const line* str), bool IsDic )
{
  TABLE_ASSERT;
  func_hash = Hash;
  for (size_t cnt = 0; cnt < strs_size; cnt++)
    insert(strs + cnt, IsDic);
  TABLE_ASSERT;
} 
bool mk5::hash_table::put_to_csv(const char file_out[], char sep_sym, const char name[])
{
  TABLE_ASSERT;
  FILE* F = fopen(file_out, "a");
  if (F == nullptr)
  {
    printf("Error with file opening");
    return false;
  }

  if (!is_header_print)
    print_csv_header(F, sep_sym);

  fprintf(F, "%s", name);
  for (size_t i = 0; i < table_size; i++)
  {
    fprintf(F, "%4d%c", table[i].get_size(), sep_sym);
  }
  fprintf(F, "\n");

  fclose(F);
  TABLE_ASSERT;
  return true;
} 
bool mk5::hash_table::table_ok(void)
{
  if (func_hash == nullptr)
  {
    printf("Hashing function was nullptr\n");
    return false;
  }
  
  table[0].get_capacity();
  int count_free = 0, count_busy = 0;
  for (size_t i = 0; i < table_size; i++) {
    count_free = 0;
    count_busy = 0;
    table[i].verification(count_free, count_busy);

    if (count_free == table[i].get_capacity() - count_busy || count_busy == table[i].get_size())
      return false;
  }
    
  return true;
} 
void mk5::hash_table::print_csv_header(FILE* f, char sep_sym)
{
  assert(f != nullptr);
  TABLE_ASSERT;

  fprintf(f, "List; ");
  for (size_t i = 0; i < table_size; i++)
  {
    fprintf(f, "%4d%c", i, sep_sym);
  }
  fprintf(f, "\n");

  is_header_print = true;
  TABLE_ASSERT;
} /* End of 'PrintCSVHeader' function */
