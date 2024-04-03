#include "../Expression.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(Test0, Test0) {
    Expression *e = new Add(new Var("x"), new Mult(new Val(10), new Var("y")));
    Expression *res1 = e->diff("x");
    string sres1 = "(1.000000 + (0.000000 * y + 10.000000 * 0.000000))";
    EXPECT_EQ(sres1, res1->getString());
    Expression *res2 = e->diff("y");
    string sres2 = "(0.000000 + (0.000000 * y + 10.000000 * 1.000000))";
    EXPECT_EQ(sres2, res2->getString());
    delete e;
    // delete res1;
    // delete res2;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
