#include "ReaderFile.h"
#include <stdexcept>

ReaderFile::ReaderFile(const char* fileName) : IOFile(fileName, "rb") {
}

char ReaderFile::readChar() {
    if (eof())
        throw std::logic_error("end of file");
    if (!isOpen_)
        throw std::logic_error("file is not open");
    return fgetc(source_);
}
