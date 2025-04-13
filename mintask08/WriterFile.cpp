#include "WriterFile.h"
#include <stdexcept>

WriterFile::WriterFile(const char* fileName) : IOFile(fileName, "wb") {
}

void WriterFile::writeByte(std::byte byte) {
    if (!isOpen_) {
        throw std::logic_error("file is not open");
    }
    fputc(static_cast<int>(byte), source_);
}
