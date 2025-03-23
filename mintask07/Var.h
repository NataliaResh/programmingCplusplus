#pragma once
#include "Expression.h"

class Var: public Expression {
  std::string id_;
  public:
    Var(std::string id);
    virtual operator std::string() const;
    virtual Expression* eval();
    virtual Expression* eval(std::map<std::string, Expression*> env);
    virtual Expression* from_env(std::map<std::string, Expression*> env);
    virtual Expression* copy();
};
