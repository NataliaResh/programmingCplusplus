#pragma once
#include "IO.h"
#include <sstream>
#include <string>

class Writer : virtual public IO {
  protected:
    virtual void writeChar(char symbol) = 0;
  public:
    template <typename T> void write(const T& input) {
        std::ostringstream string_stream;
        string_stream << input;
        for(auto symbol: string_stream.str()) {
            writeChar(symbol);
        }
        writeChar(' ');
    }

    void write(const char& input) {
      writeChar(input);
    }

    void writeString(const std::string& input);
};
