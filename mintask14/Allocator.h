#include <cstddef>
#include <new>
#include <type_traits>
#include <vector>

template<typename... Types>
consteval size_t get_size() {
  size_t size = 0;
  ((size = ((size + alignof(Types) - 1) & ~(alignof(Types) - 1)) + sizeof(Types)), ...);
  return size;
}

template <size_t SIZE, typename... Types>
requires(std::is_copy_constructible_v<Types> &&...) &&
    (SIZE >= get_size<Types...>())
void allocate(void *memory, Types... args) {
  char* pointer = static_cast<char *>(memory);
  (([&]() {
     pointer = reinterpret_cast<char*>((reinterpret_cast<size_t>(pointer) + alignof(Types) - 1) & ~(alignof(Types) - 1));
     new (pointer) Types(args);
     pointer += sizeof(Types);
   })(), ...);
}
