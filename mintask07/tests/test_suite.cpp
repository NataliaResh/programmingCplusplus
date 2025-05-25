#include "../Add.h"
#include "../Call.h"
#include "../Expression.h"
#include "../Function.h"
#include "../If.h"
#include "../Let.h"
#include "../Parser.h"
#include "../Val.h"
#include "../Var.h"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

TEST(Test0, Test0) {
    unique_ptr<Expression> e(new Let("K", new Val(10), new Add(new Val(5), new Var("K"))));
    unique_ptr<Expression> result(e.get()->eval());
    string str = static_cast<std::string>(*result);
    Parser parser;
    unique_ptr<Expression> e2(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e2), str);
    EXPECT_EQ(result.get()->get_value(), 15);
}

TEST(Test1, Test1) {
    unique_ptr<Expression> e(
        new Let("A", new Val(20),
                new Let("B", new Val(30),
                        new If(new Var("A"), new Add(new Var("B"), new Val(3)), new Val(10),
                               new Add(new Var("B"), new Val(1))))));
    unique_ptr<Expression> result(e.get()->eval());
    string str = static_cast<std::string>(*result);
    Parser parser;
    unique_ptr<Expression> e2(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e2), str);
    EXPECT_EQ(result.get()->get_value(), 31);
}

TEST(Test2, Test2) {
    unique_ptr<Expression> e(
        new Let("F", new Function("arg", new Add(new Var("arg"), new Val(1))),
                new Let("V", new Val(-1), new Call(new Var("F"), new Var("V")))));
    unique_ptr<Expression> result(e.get()->eval());
    string str = static_cast<std::string>(*result);
    Parser parser;
    unique_ptr<Expression> e2(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e2), str);
    EXPECT_EQ(result.get()->get_value(), 0);
}

TEST(Test3, Test3) {
    //unique_ptr<Expression> e(new Add(new Var("A"), new Var("B")));
    //try {
    //    Expression* result = e.get()->eval();
    //    EXPECT_FALSE(true);
    //} catch (const ExpressionException& e) {
    //    EXPECT_TRUE(true);
    //}

}

TEST(Test4, Test4) {
    Parser parser;
    std::string str = "(add (var A) (var B))";
    unique_ptr<Expression> e(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e), str);

}

TEST(Test5, Test5) {
    Parser parser;
    std::string str = "(if (var A) (add (var B) (val 3)) then (val 10) else (add (var B) (val 1)))";
    unique_ptr<Expression> e(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e), str);
}

TEST(Test6, Test6) {
    Parser parser;
    std::string str = "(if (var A) (add (var B) (val 3)) then (val 10) else (add (var B) (val 1)))";
    unique_ptr<Expression> e(parser.parse(str));
    EXPECT_EQ(static_cast<string>(*e), str);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
