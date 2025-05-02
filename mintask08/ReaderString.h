#pragma once
#include "IOString.h"
#include "Reader.h"
#include <string>

class ReaderString : virtual public Reader, virtual public IOString {
  protected:
    char readChar() override;

  public:
    explicit ReaderString(std::string source);
};
