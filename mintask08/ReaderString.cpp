#include "ReaderString.h"

#include <utility>

ReaderString::ReaderString(std::string source) : IOString(std::move(source)) {
}

std::byte ReaderString::readByte() {
    if (eof() || !isOpen_)
        throw;
    return static_cast<std::byte>(source_[position_++]);
}