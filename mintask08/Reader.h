#pragma once
#include "IO.h"
#include <string>

class Reader : virtual public IO {
  protected:
    virtual std::byte readByte() = 0;
  public:
    template <typename T> T read() {
        size_t size = sizeof(T);
        T output;
        auto* bytes = reinterpret_cast<std::byte*>(&output);
        for (size_t i = 0; i < size; i++) {
            bytes[i] = readByte();
        }
        return output;
    }

    std::string readString();
};
