#include "ReaderWriterFile.h"
#include <iostream>

ReaderWriterFile::ReaderWriterFile(const char* fileName)
    : IOFile(fileName, "r+b"), ReaderFile(fileName), WriterFile(fileName) {
}