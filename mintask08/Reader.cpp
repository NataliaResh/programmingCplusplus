#include "Reader.h"

std::string Reader::readString() {
    std::string output;
    char byte = static_cast<char>(readByte());
    while (byte != '\0') {
        output += byte;
        byte = static_cast<char>(readByte());
    }
    return output;
}
