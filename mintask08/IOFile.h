#pragma once
#include "IO.h"
#include <cstdio>

class IOFile : virtual public IO {
  protected:
    const char* fileName_;
    FILE* source_ = nullptr;
    const char* mode_;

  public:
    explicit IOFile(const char* fileName, const char* mode);
    bool open() override;
    bool close() override;
    bool eof() const override;
    ~IOFile();
};
