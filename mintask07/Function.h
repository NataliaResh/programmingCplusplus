#pragma once
#include "Expression.h"

class Function: public Expression {
  public:
  std::string id_;
  Expression* e_body_;

  public:
    Function(std::string id, Expression* e_body);
    virtual operator std::string() const;
    virtual Expression* eval();
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    ~Function();
  };
