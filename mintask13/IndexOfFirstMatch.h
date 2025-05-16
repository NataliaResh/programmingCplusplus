#include <utility>

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args&&... args) {
  int i = 0;
  bool checker = ([&]() {
    if (check(std::forward<decltype(args)>(args))) {
      return true;
    }
    i++;
    return false;
  }() || ...);
  return checker ? i : -1 ;
}
