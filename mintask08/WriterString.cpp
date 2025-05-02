#include "WriterString.h"

#include <utility>

WriterString::WriterString(std::string source) : IOString(std::move(source)) {
}

void WriterString::writeChar(char symbol) {
    if (!isOpen_)
        throw;
    source_ += symbol;
}
