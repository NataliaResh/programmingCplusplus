#include "Expression.h"

int Expression::get_value() {
  throw ExpressionException("Can't get value from not value type!");
}
