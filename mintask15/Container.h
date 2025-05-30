#include "Allocator.h"
#include <utility>
#include <iostream>

template<typename... Types>
class Container {
  char memory[get_size<Types...>()]{};
  std::vector<char*> pointers;
  public:
    explicit Container(Types&&... args) {
      pointers = allocate<get_size<Types...>()>(memory, std::forward<Types>(args)...);
    }

    template<typename T>
    T getElement(size_t idx) {
      return *(reinterpret_cast<T*>(pointers[idx]));
    }

    ~Container() {
        size_t i = 0;
        ((reinterpret_cast<Types*>(pointers[i++])->~Types(), ...));
    }
};

