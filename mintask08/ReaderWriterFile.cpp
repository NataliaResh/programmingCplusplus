#include "ReaderWriterFile.h"
#include <cstdio>

ReaderWriterFile::ReaderWriterFile(const char* fileName, const char* mode)
    : fileName_(fileName), mode_(mode) {
}

bool ReaderWriterFile::open() {
    if (isOpen_)
        return false;
    try {

        source_ = fopen(fileName_, mode_);

    } catch (...) {
        return false;
    }
    isOpen_ = true;
    return true;
}

bool ReaderWriterFile::close() {
    if (!isOpen_)
        return false;
    try {
        fclose(source_);
    } catch (...) {
        return false;
    }
    isOpen_ = false;
    return true;
}

bool ReaderWriterFile::eof() const {
    return feof(source_);
}

std::byte ReaderWriterFile::readByte() {
    if (eof() || !isOpen_)
        throw;
    return static_cast<std::byte>(fgetc(source_));
}

void ReaderWriterFile::writeByte(std::byte byte) {
    if (!isOpen_)
        throw;
    fputc(static_cast<int>(byte), source_);
}

ReaderWriterFile::~ReaderWriterFile() {
    if (isOpen_) {
        fclose(source_);
    }
}

