#include <utility>
#include <iostream>

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args&&... args) {
  int ans = 0;
  bool match = ([&] {
    if (check(std::forward<Args>(args))) {
      return true;
    }
    ans++;
    return false;
  }() || ...);
  if (match) return ans;
  return -1;
}

bool isOdd(int n) {
  return n & 1;
}

int main() {
  std::cout << getIndexOfFirstMatch(isOdd, 2, 1, 3) << "\n";
  std::cout << getIndexOfFirstMatch(isOdd, 1, 2, 3) << "\n";
  std::cout << getIndexOfFirstMatch(isOdd) << "\n";
  std::cout << getIndexOfFirstMatch(isOdd, 0, 2, 4) << "\n";

}
