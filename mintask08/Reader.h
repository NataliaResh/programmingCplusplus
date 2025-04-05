#pragma once
#include "IO.h"
#include <string>

class Reader : virtual public IO {
  public:
    template <typename T> T read() {
        size_t size = sizeof(T);
        T output;
        std::byte* bytes = reinterpret_cast<std::byte*>(&output);
        for (size_t i = 0; i < size; i++) {
            bytes[i] = readByte();
        }
        return output;
    }

    std::string readString();
};
