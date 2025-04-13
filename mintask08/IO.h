#pragma once
#include <algorithm>

class IO {
  protected:
    bool isOpen_ = false;

  public:
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool eof() const = 0;
};
