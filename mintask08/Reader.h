#pragma once
#include "IO.h"
#include <sstream>
#include <string>

class Reader : virtual public IO {
  protected:
    virtual char readChar() = 0;
  public:
    template <typename T> T read() {
        std::basic_string<char> symbol;
        do {
            symbol = readChar();
        } while(std::isspace(symbol.back()));
        std::string output(symbol);
        while (!eof()) {
            symbol = readChar();
            if (std::isspace(symbol.back())) {
                break;
            }
            output += symbol;
        }
        std::istringstream string_stream(output);
        T result;
        string_stream >> result;
        return result;
    }

    std::string readString();
};
