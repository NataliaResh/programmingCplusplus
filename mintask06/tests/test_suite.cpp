#include "../SquareMatrix.cpp"
#include <exception>
#include <gtest/gtest.h>

using namespace std;

TEST(Test0, Test0) {
    SquareMatrix m1 = SquareMatrix({1, 2, 3, 4});
    EXPECT_EQ(static_cast<double>(m1), 10.0);
    SquareMatrix m2 = SquareMatrix(4);
    for (size_t i = 0; i < m2.size(); i++)
        for (size_t j = 0; j < m2.size(); j++)
            m2[i][j] = i + j;
    SquareMatrix m3 = m1;
    EXPECT_TRUE(m1 == m3);
    m3[0][1] = 2;
    EXPECT_TRUE(m1 != m3);
    EXPECT_EQ(m1[0][1], 0);
    SquareMatrix m4 = m1 + m2;
    EXPECT_EQ(m4[0][0], 1);
    EXPECT_EQ(m4[0][1], 1);
    m4 = (m1 * 2);
    m4 *= m2;
    double ans[4][4] = {{0, 2, 4, 6}, {4, 8, 12, 16}, {12, 18, 24, 30}, {24, 32, 40, 48}};
    for (size_t i = 0; i < m4.size(); i++)
        for (size_t j = 0; j < m4.size(); j++)
            EXPECT_EQ(m4[i][j], ans[i][j]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
