#include "WriterFile.h"
#include <stdexcept>

WriterFile::WriterFile(const char* fileName) : IOFile(fileName, "wb") {
}

void WriterFile::writeChar(char symbol) {
    if (!isOpen_) {
        throw std::logic_error("file is not open");
    }
    fputc(symbol, source_);
}
