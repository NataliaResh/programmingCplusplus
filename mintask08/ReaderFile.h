#pragma once
#include "IOFile.h"
#include "Reader.h"

class ReaderFile : virtual public Reader, virtual public IOFile {
  protected:
    std::byte readByte() override;

  public:
    explicit ReaderFile(const char *fileName);
};
