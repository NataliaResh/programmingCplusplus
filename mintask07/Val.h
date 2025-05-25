#pragma once
#include "Expression.h"
#include <string>

class Val : public Expression {
    int value_;

  public:
    Val(int value);
    virtual operator std::string() const;
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    virtual int get_value();
    ~Val();
};
