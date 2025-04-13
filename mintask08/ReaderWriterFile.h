#pragma once
#include "ReaderWriter.h"
#include <fstream>
#include <cstdio>

class ReaderWriterFile : public ReaderWriter {
    const char* fileName_;
    FILE* source_{};
    const char* mode_;

  public:
    ReaderWriterFile(const char* fileName, const char* mode);

    bool open() override;

    bool close() override;

    bool eof() const override;

    std::byte readByte() override;

    void writeByte(std::byte byte) override;

    ~ReaderWriterFile();
};
