#include "ExpressionException.h"

ExpressionException::ExpressionException(std::string msg) :  message_(msg) {}

const char* ExpressionException::what() const throw() {
  return message_.c_str();
}
