#pragma once
#include "ReaderFile.h"
#include "ReaderWriter.h"
#include "WriterFile.h"

class ReaderWriterFile : public ReaderWriter, public ReaderFile, public WriterFile {
  public:
    explicit ReaderWriterFile(const char* fileName);
};
