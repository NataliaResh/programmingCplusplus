#include "ReaderWriterString.h"

ReaderWriterString::ReaderWriterString(const std::string& source)
    : ReaderString(source), WriterString(source), IOString(source) {
}