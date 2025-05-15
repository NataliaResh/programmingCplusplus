#pragma once
#include "IOString.h"
#include "Writer.h"
#include <string>

class WriterString : virtual public Writer, virtual public IOString {
  protected:
    void writeChar(char symbol) override;

  public:
    explicit WriterString(std::string source);
};