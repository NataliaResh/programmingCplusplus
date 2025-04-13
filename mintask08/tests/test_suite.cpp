#include "../ReaderWriterFile.h"
#include "../ReaderWriterString.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace std;

void testWrite(Writer& writer) {
    writer.open();
    writer.writeString("aaa");
    writer.write<int>(10);
    writer.write<char>('a');
    writer.write<bool>(true);
    writer.write<double>(1.2);
    try {
        writer.close();
    } catch (std::logic_error& e) {
        std::cout << e.what();
    }
}

void testRead(Reader& reader) {
    reader.open();
    EXPECT_EQ(reader.readString(), "aaa");
    EXPECT_EQ(reader.read<int>(), 10);
    EXPECT_EQ(reader.read<char>(), 'a');
    EXPECT_EQ(reader.read<bool>(), true);
    EXPECT_EQ(reader.read<double>(), 1.2);
    try {
        reader.close();
    } catch (std::logic_error& e) {
        std::cout << e.what();
    }
}

TEST(Test0, Test0) {
    ReaderWriterString rwStr = ReaderWriterString("");
    testWrite(rwStr);
    testRead(rwStr);
}

TEST(Test1, Test1) {
    ReaderWriterFile rwFile = ReaderWriterFile("test");
    testWrite(rwFile);
    testRead(rwFile);
}

TEST(Test2, Test2) {
    WriterString ws = WriterString("");
    testWrite(ws);
    std::string result = ws.getString();
    ReaderString rs = ReaderString(result);
    testRead(rs);
}

TEST(Test3, Test3) {
    WriterFile wf = WriterFile("test");
    testWrite(wf);
    ReaderFile rf = ReaderFile("test");
    testRead(rf);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
