#pragma once
#include "IOFile.h"
#include "Reader.h"

class ReaderFile : virtual public Reader, virtual public IOFile {
  protected:
    char readChar() override;

  public:
    explicit ReaderFile(const char *fileName);
};
