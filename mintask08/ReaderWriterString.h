#pragma once
#include "ReaderWriter.h"

class ReaderWriterString : public ReaderWriter {
    std::string source_;
    size_t position_ = 0;

  public:
    explicit ReaderWriterString(std::string source);

    bool open() override;

    bool close() override;

    bool eof() const override;

    std::byte readByte() override;

    void writeByte(std::byte byte) override;

    std::string getString() const;
};
