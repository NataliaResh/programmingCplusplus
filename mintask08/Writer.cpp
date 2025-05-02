#include "Writer.h"

void Writer::writeString(const std::string& input) {
    for (auto& symbol : input) {
        writeChar(symbol);
    }
    writeChar('\0');
}
