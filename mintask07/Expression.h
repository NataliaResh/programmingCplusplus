#pragma once
#include "ExpressionException.h"
#include <map>
#include <string>

class Expression {
  public:
    Expression* eval();
    virtual Expression* eval(std::map<std::string, Expression*>) = 0;
    virtual int get_value();
    virtual operator std::string() const = 0;
    virtual Expression* copy() = 0;
    virtual ~Expression() = default;
};
