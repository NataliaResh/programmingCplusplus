#pragma once
#include "IO.h"
#include <string>

class Writer : virtual public IO {
  protected:
    virtual void writeByte(std::byte byte) = 0;
  public:
    template <typename T> void write(T input) {
        size_t size = sizeof(T);
        auto* bytes = reinterpret_cast<std::byte*>(&input);
        for (size_t i = 0; i < size; i++) {
            writeByte(bytes[i]);
        }
    }

    void writeString(const std::string& input);
};
