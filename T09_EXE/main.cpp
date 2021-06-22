#include "buffer.h"
#include "trans.h"
#include "line.h"

const int size_max = 1000;
int main(void) {

  mk5::buffer in(1000);
  char filename[size_max] = "factorial1.mk5asme";

  in.fill(filename);
  mk5::buffer out(0x1000);


  while (simplify(in));
  
  translate(in, out);
  

  out.put("solveq.txt");
  create_exe("test.exe", out);
  printf("\n%d", '\n');
  return 0x1E;
}   