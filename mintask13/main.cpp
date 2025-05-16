#include "IndexOfFirstMatch.h"
#include <cassert>

bool isOdd(int n) {
  return n & 1;
}

int main() {
  assert(getIndexOfFirstMatch(isOdd, 2, 1, 3) == 1);
  assert(getIndexOfFirstMatch(isOdd, 1, 2, 3) == 0);
  assert(getIndexOfFirstMatch(isOdd) == -1);
  assert(getIndexOfFirstMatch(isOdd, 0, 2, 4) == -1);
}
