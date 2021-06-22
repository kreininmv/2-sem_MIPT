#include "line.h"

std::ostream& operator<< (std::ostream& out, const mk5::line& myline) {

  for (int i = 0; i < myline.len; i++)
    out << myline.str[i];

  return out;
}

int file_length(FILE* file) {
  fseek(file, 0, SEEK_END);
  return ftell(file);
}


char* load_create_strings(const char filename[], size_t* str_count) {
  assert(filename != nullptr);
  
  FILE* f = fopen(filename, "rb");

  if (f == NULL)
    return nullptr;
  
  int len = file_length(f);

  if (len <= 0) {
    fclose(f);
    return nullptr;
  }
    

  char* buf = new char[len + 1]{ 0 };
  //char buf[120] = { 0 };

  if (buf == nullptr) {
    fclose(f);
    return nullptr;
  }
  
  rewind(f);

  fread(buf, sizeof(char), len, f);

  if (str_count != nullptr)
    *str_count = len;

  fclose(f);

  return buf;
}