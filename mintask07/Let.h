#pragma once
#include "Expression.h"
#include <map>

class Let : public Expression {
    std::string id_;
    Expression* e_value_;
    Expression* e_body_;

  public:
    Let(std::string id, Expression* e_value, Expression* e_body);
    virtual operator std::string() const;
    virtual Expression* eval(std::map<std::string, Expression*>);
    virtual Expression* copy();
    ~Let();
};
