#include "../Expression.cpp"
#include <exception>
#include <gtest/gtest.h>
#include <string>
#include <iostream>
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
    delete res1;
    delete res2;
}

TEST(Test1, Test1) {
    Expression *e = new Val(2);
    Expression *res1 = e->diff("x");
    string sres1 = "0.000000";
    EXPECT_EQ(sres1, res1->getString());
    delete e;
    delete res1;
}

TEST(Test2, Test2) {
    Expression *e = new Var("x");
    Expression *res1 = e->diff("x");
    string sres1 = "1.000000";
    EXPECT_EQ(sres1, res1->getString());
    Expression *res2 = e->diff("y");
    string sres2 = "0.000000";
    EXPECT_EQ(sres2, res2->getString());
    delete e;
    delete res1;
    delete res2;
}

TEST(Test3, Test3) {
    Expression *e = new Exponent(new Mult(new Val(3), new Var("x")));
    Expression *res1 = e->diff("x");
    string sres1 = "e ^ (3.000000 * x) * (0.000000 * x + 3.000000 * 1.000000)";
    EXPECT_EQ(sres1, res1->getString());
    delete e;
    delete res1;
}

TEST(Test4, Test4) {
    Expression *e = new Div(new Mult(new Val(3), new Var("x")), new Sub(new Var("x"), new Val(2)));
    Expression *res1 = e->diff("x");
    string sres1 = "(((0.000000 * x + 3.000000 * 1.000000) * (x - 2.000000) - 3.000000 * x * (1.000000 - 0.000000))) / ((x - 2.000000) * (x - 2.000000))";
    EXPECT_EQ(sres1, res1->getString());
    delete e;
    delete res1;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
