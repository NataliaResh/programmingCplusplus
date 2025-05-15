#include "IOString.h"

IOString::IOString(std::string source) : source_(std::move(source)) {
}

bool IOString::open() {
    if (isOpen_)
        return false;
    isOpen_ = true;
    return true;
}

bool IOString::close() {
    if (!isOpen_)
        return false;
    isOpen_ = false;
    return true;
}

bool IOString::eof() const {
    return position_ == source_.length();
}

std::string IOString::getString() const {
    return source_;
}