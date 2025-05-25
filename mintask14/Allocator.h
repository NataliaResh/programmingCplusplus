#include <cstddef>
#include <new>
#include <type_traits>

template <size_t SIZE, typename... Types>
requires(std::is_copy_constructible_v<Types> &&...) &&
    (SIZE >= (0 + ... + sizeof(Types))) void allocate(void *memory,
                                                      Types... args) {
  char *pointer = static_cast<char *>(memory);
  (([&]() {
     new (pointer) Types(args);
     pointer += sizeof(Types);
   })(),
   ...);
}
