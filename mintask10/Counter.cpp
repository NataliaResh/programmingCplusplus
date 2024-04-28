#include <cstddef>
#include <string>
#include <iostream>


class MaxCountInstances : public std::exception {
  std::string msg_;
  public:
  MaxCountInstances(size_t limit) {
    msg_ = "Try to create more than ";
    msg_ += std::to_string(limit);
    msg_ += " instances of class!";
  }
};

template <typename T, size_t limit>
struct Counter {
  static inline size_t objects;
  void incObjects() {
    if (objects >= limit)
      throw MaxCountInstances(limit);
    ++objects;
  }

  Counter() {
    incObjects();
  }

  Counter(const Counter&) {
    incObjects();
  }

  ~Counter() {
    --objects;
  }
};
