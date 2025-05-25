#include "Add.h"

Add::Add(Expression* exp1, Expression* exp2) : exp1_(exp1), exp2_(exp2) {
}

Add::operator std::string() const {
    return "(add " + static_cast<std::string>(*exp1_) + " " + static_cast<std::string>(*exp2_) +
           ")";
}

Expression* Add::eval() {
    std::map<std::string, Expression*> env;
    return eval(env);
}

Expression* Add::eval(std::map<std::string, Expression*> env) {
    Expression* value_1 = exp1_->eval(env);
    Expression* value_2 = exp2_->eval(env);
    int result = value_1->get_value() + value_2->get_value();
    delete value_1;
    delete value_2;
    return new Val(result);
}

Add::~Add() {
    if (exp1_) {
        delete exp1_;
    }
    if (exp2_) {
        delete exp2_;
    }
}

Expression* Add::copy() {
	return new Add(exp1_->copy(), exp2_->copy());
}
