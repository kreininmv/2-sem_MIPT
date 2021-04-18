#include "line.h"

std::ostream& operator<< (std::ostream& out, const mk5::line& myline) {

  for (int i = 0; i < myline.len; i++)
    out << myline.str[i];

  return out;
}