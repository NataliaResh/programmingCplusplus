#include <utility>

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args&&... args) {
  int i = 0;
  bool checker = ([&](auto&& arg) {
    if (check(std::forward<decltype(arg)>(arg))) {
      return true;
    }
    i++;
    return false;
  }(args) || ...);
  return checker ? i : -1 ;
}
