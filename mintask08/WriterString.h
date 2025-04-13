#pragma once
#include "IOString.h"
#include "Writer.h"
#include <string>

class WriterString : virtual public Writer, virtual public IOString {
  protected:
    void writeByte(std::byte byte) override;

  public:
    explicit WriterString(std::string source);
};