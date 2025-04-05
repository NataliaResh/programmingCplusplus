#pragma once
#include "ReaderWriter.h"

class ReaderWriterString : public ReaderWriter {
    std::string source_ = "";
    size_t position_ = 0;

  public:
    ReaderWriterString(std::string source);

    bool open();

    bool close();

    bool eof() const;

    std::byte readByte();

    void writeByte(std::byte byte);

    std::string getString() const;
};
