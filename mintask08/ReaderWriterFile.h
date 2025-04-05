#pragma once
#include "ReaderWriter.h"
#include <fstream>
#include <stdio.h>

class ReaderWriterFile : public ReaderWriter {
    const char* fileName_;
    FILE* source_;
    const char* mode_;

  public:
    ReaderWriterFile(const char* fileName, const char* mode);

    bool open();

    bool close();

    bool eof() const;

    std::byte readByte();

    void writeByte(std::byte byte);

    ~ReaderWriterFile();
};
