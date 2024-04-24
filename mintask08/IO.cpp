#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

class IO {
  protected:
    bool isOpen_ = false;
    virtual std::byte readByte() = 0;
    virtual void writeByte(std::byte byte) = 0;

  public:
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool eof() = 0;
};

class Reader : virtual public IO {
  public:
    template <typename T> T read() {
        size_t size = sizeof(T);
        T output;
        std::byte* bytes = reinterpret_cast<std::byte*>(&output);
        for (size_t i = 0; i < size; i++) {
            bytes[i] = readByte();
        }
        return output;
    }

    std::string readString() {
        std::string output = "";
        char byte = static_cast<char>(readByte());
        while (byte != '\0') {
            output += byte;
            byte = static_cast<char>(readByte());
        }
        return output;
    }
};

class Writer : virtual public IO {
  public:
    template <typename T> void write(T input) {
        size_t size = sizeof(T);
        std::byte* bytes = reinterpret_cast<std::byte*>(&input);
        for (size_t i = 0; i < size; i++) {
            writeByte(bytes[i]);
        }
    }

    void writeString(std::string input) {
        for (auto& byte : input) {
            writeByte(static_cast<std::byte>(byte));
        }
        writeByte(static_cast<std::byte>('\0'));
    }
};

class ReaderWriter : public Reader, public Writer {};

class ReaderWriterString : public ReaderWriter {
    std::string source_ = "";
    size_t position_ = 0;

  public:
    ReaderWriterString(std::string source) : source_(source) {
    }

    bool open() {
        if (isOpen_)
            return false;
        isOpen_ = true;
        return true;
    }

    bool close() {
        if (!isOpen_)
            return false;
        isOpen_ = false;
        return true;
    }

    bool eof() {
        return position_ == source_.size();
    }

    std::byte readByte() {
        if (eof() || !isOpen_)
            throw;
        return static_cast<std::byte>(source_[position_++]);
    }

    void writeByte(std::byte byte) {
        if (!isOpen_)
            throw;
        source_ += static_cast<char>(byte);
    }

    std::string getString() {
        return source_;
    }
};

class ReaderWriterFile : public ReaderWriter {
    const char* fileName_;
    FILE* source_;
    const char* mode_;

  public:
    ReaderWriterFile(const char* fileName, const char* mode) : fileName_(fileName), mode_(mode) {
    }

    bool open() {
        if (isOpen_)
            return false;
        try {

            source_ = fopen(fileName_, mode_);

        } catch (...) {
            return false;
        }
        isOpen_ = true;
        return true;
    }

    bool close() {
        if (!isOpen_)
            return false;
        try {
            fclose(source_);
        } catch (...) {
            return false;
        }
        isOpen_ = false;
        return true;
    }

    bool eof() {
        return feof(source_);
    }

    std::byte readByte() {
        if (eof() || !isOpen_)
            throw;
        return static_cast<std::byte>(fgetc(source_));
    }

    void writeByte(std::byte byte) {
        if (!isOpen_)
            throw;
        fputc(static_cast<int>(byte), source_);
    }
};
