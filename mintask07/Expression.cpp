#include "Expression.h"
#include <exception>
#include <iostream>
int Expression::get_value() {
  throw ExpressionException("Can't get value from not value type!");
}

Expression::~Expression() {
}
