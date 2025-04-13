#include "ReaderFile.h"
#include <stdexcept>

ReaderFile::ReaderFile(const char* fileName) : IOFile(fileName, "rb") {
}

std::byte ReaderFile::readByte() {
    if (eof())
        throw std::logic_error("end of file");
    if (!isOpen_)
        throw std::logic_error("file is not open");
    return static_cast<std::byte>(fgetc(source_));
}