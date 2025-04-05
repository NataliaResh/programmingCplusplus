#include "ReaderWriterString.h"

ReaderWriterString::ReaderWriterString(std::string source) : source_(source) {
}

bool ReaderWriterString::open() {
    if (isOpen_)
        return false;
    isOpen_ = true;
    return true;
}

bool ReaderWriterString::close() {
    if (!isOpen_)
        return false;
    isOpen_ = false;
    return true;
}

bool ReaderWriterString::eof() const {
    return position_ == source_.size();
}

std::byte ReaderWriterString::readByte() {
    if (eof() || !isOpen_)
        throw;
    return static_cast<std::byte>(source_[position_++]);
}

void ReaderWriterString::writeByte(std::byte byte) {
    if (!isOpen_)
        throw;
    source_ += static_cast<char>(byte);
}

std::string ReaderWriterString::getString() const {
    return source_;
}
