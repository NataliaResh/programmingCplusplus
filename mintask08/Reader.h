#pragma once
#include "IO.h"
#include <sstream>
#include <string>

namespace reader {
  template <typename T> T read();
  template <> char read<char>();
}

class Reader : virtual public IO {
  protected:
    virtual char readChar() = 0;
  public:
    template <typename T> T read() {
        char symbol;
        do {
            symbol = readChar();
        } while(std::isspace(symbol));
        std::string output;
        output += symbol;
        while (!eof()) {
            symbol = readChar();
            if (std::isspace(symbol)) {
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
