#pragma once
#include "Expression.h"
#include "Function.h"

class Call: public Expression {
  Expression* f_exp_;
  Expression* arg_exp_;

  public:
    Call(Expression* f_exp_, Expression* arg_exp_);
    virtual operator std::string() const;
    virtual Expression* eval();
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    ~Call();
  };
