#pragma once
#include "IOFile.h"
#include "Writer.h"

class WriterFile : virtual public Writer, virtual public IOFile {
  protected:
    void writeByte(std::byte byte) override;

  public:
    explicit WriterFile(const char* fileName);
};