#include "Writer.h"

void Writer::writeString(std::string input) {
    for (auto& byte : input) {
        writeByte(static_cast<std::byte>(byte));
    }
    writeByte(static_cast<std::byte>('\0'));
}
