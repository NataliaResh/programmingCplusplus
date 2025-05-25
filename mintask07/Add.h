#pragma once
#include "Expression.h"
#include "Val.h"

class Add: public Expression {
  Expression* exp1_;
  Expression* exp2_;
  public:
    Add(Expression* exp1, Expression* exp2);
    virtual operator std::string() const;
    virtual Expression* eval();
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    ~Add();
};

