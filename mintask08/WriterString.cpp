#include "WriterString.h"

#include <utility>

WriterString::WriterString(std::string source) : IOString(std::move(source)) {
}

void WriterString::writeByte(std::byte byte) {
    if (!isOpen_)
        throw;
    source_ += static_cast<char>(byte);
}
