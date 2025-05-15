#pragma once
#include "IO.h"
#include <string>

class IOString : virtual public IO {
  protected:
    std::string source_;
    size_t position_ = 0;

  public:
    explicit IOString(std::string source);
    bool open() override;
    bool close() override;
    bool eof() const override;
    std::string getString() const;
};