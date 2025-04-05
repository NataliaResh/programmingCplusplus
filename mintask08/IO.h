#pragma once
#include <algorithm>

class IO {
  protected:
    bool isOpen_ = false;
    virtual std::byte readByte() = 0;
    virtual void writeByte(std::byte byte) = 0;

  public:
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool eof() const = 0;
};
