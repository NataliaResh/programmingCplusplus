#include "ReaderString.h"

#include <utility>

ReaderString::ReaderString(std::string source) : IOString(std::move(source)) {
}

char ReaderString::readChar() {
    if (eof() || !isOpen_)
        throw std::logic_error("end of string");;
    return source_[position_++];
}

//std::string ReaderString::readToken() {
//    for (; position_ < source_.size() && std::isspace(source_[position_]); ++position_) {
//    }
//    std::string output;
//    for (; position_ < source_.size() && !std::isspace(source_[position_]); ++position_) {
//        output += source_[position_];
//    }
//    return output;
//}
