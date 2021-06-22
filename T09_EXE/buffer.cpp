#include "buffer.h"
#include <assert.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "line.h"

mk5::buffer::buffer(void) : buf(nullptr), size(0)
{}

mk5::buffer::buffer(size_t size, char init) : buf(new char[size]{init}), size(size)
{}

mk5::buffer::buffer(buffer&& buf) : buf(buf.buf), size(buf.size)
{}

void mk5::buffer::fill(const char filename[]) {
  assert(filename != nullptr);
  buf = load_create_strings(filename, &this->size);
}

bool mk5::buffer::put(const char filename[]) {
  assert(filename != nullptr);
  assert(buf != nullptr);
  assert(size != 0);

  FILE* out = fopen(filename, "wb");

  if (out == nullptr)
    return false;

  fwrite(buf, sizeof(char), size, out);

  fclose(out);

  return true;
}

char& mk5::buffer::operator[](size_t index) {
  return buf[index];
}

mk5::buffer::~buffer(void) {
  if (buf != nullptr)
    delete[] buf;
}

