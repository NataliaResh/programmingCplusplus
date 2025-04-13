#include "Writer.h"

void Writer::writeString(const std::string& input) {
    for (auto& byte : input) {
        writeByte(static_cast<std::byte>(byte));
    }
    writeByte(static_cast<std::byte>('\0'));
}
