#include "../IO.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>
#include <iostream>
using namespace std;

TEST(Test0, Test0) {
    ReaderWriterString wStr = ReaderWriterString("");
    wStr.open();
    wStr.writeString("aaa");
    wStr.write<int>(10);
    std::string str = wStr.getString();
    ReaderWriterString rStr = ReaderWriterString(str);
    rStr.open();
    EXPECT_EQ(rStr.readString(), "aaa");
    EXPECT_EQ(rStr.read<int>(), 10);
    rStr.close();
}

TEST(Test1, Test1) {
    ReaderWriterFile wFile = ReaderWriterFile("test", "wb");
    wFile.open();
    wFile.writeString("aaa");
    wFile.write<int>(10);
    wFile.close();
    ReaderWriterFile rFile = ReaderWriterFile("test", "rb");
    rFile.open();
    EXPECT_EQ(rFile.readString(), "aaa");
    EXPECT_EQ(rFile.read<int>(), 10);
    rFile.close();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
