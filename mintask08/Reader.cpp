#include "Reader.h"

std::string Reader::readString() {
    std::string output;
    char byte = static_cast<char>(readChar());
    while (byte != '\0') {
        output += byte;
        byte = static_cast<char>(readChar());
    }
    return output;
}
