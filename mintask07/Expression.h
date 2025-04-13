#pragma once
#include <string>
#include <map>
#include "ExpressionException.h"

class Expression {
  public:
  virtual Expression* eval() = 0;
  virtual Expression* eval(std::map<std::string, Expression*>) = 0;
  virtual int get_value();
  virtual operator std::string() const = 0;
  virtual Expression* copy() = 0;
  virtual ~Expression() = default;
};
