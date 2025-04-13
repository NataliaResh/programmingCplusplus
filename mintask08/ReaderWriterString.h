#pragma once
#include "IOString.h"
#include "ReaderString.h"
#include "ReaderWriter.h"
#include "WriterString.h"

class ReaderWriterString : public ReaderWriter, public ReaderString, public WriterString {
  public:
    explicit ReaderWriterString(const std::string& source);
};
