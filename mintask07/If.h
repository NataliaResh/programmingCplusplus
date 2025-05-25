#pragma once
#include "Expression.h"

class If : public Expression {
    Expression* e1_;
    Expression* e2_;
    Expression* e_then_;
    Expression* e_else_;

  public:
    If(Expression* e1, Expression* e2_, Expression* e_then, Expression* e_else);
    virtual operator std::string() const;
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    ~If();
};
