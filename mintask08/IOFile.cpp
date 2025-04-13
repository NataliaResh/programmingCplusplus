#include "IOFile.h"
#include <stdexcept>

IOFile::IOFile(const char* fileName, const char* mode) : fileName_(fileName), mode_(mode) {
}

bool IOFile::open() {
    if (isOpen_)
        return false;

    source_ = fopen(fileName_, mode_);

    isOpen_ = source_ != nullptr;
    return isOpen_;
}

bool IOFile::close() {
    if (!isOpen_)
        return false;
    int result = fclose(source_);
    if (result == EOF) {
        throw std::logic_error("file is not closed");
    }
    isOpen_ = false;

    return true;
}

bool IOFile::eof() const {
    return feof(source_);
}

IOFile::~IOFile() {
    if (isOpen_) {
        fclose(source_);
    }
}