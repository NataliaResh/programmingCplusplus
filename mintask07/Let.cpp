#include "Let.h"

Let::Let(std::string id, Expression* e_value, Expression* e_body)
    : id_(id), e_value_(e_value), e_body_(e_body) {
}

Let::operator std::string() const {
    return "(let " + id_ + " = " + static_cast<std::string>(*e_value_) + " in " +
           static_cast<std::string>(*e_body_) + ")";
}

Expression* Let::eval() {
    std::map<std::string, Expression*> env;
    env.insert({id_, e_value_});
    return e_body_->eval(env);
}

Expression* Let::eval(std::map<std::string, Expression*> env) {
    env.insert({id_, e_value_});
    return e_body_->eval(env);
}

Let::~Let() {
    if (e_value_) {
        delete e_value_;
    }
    if (e_body_) {
        delete e_body_;
    }
}

Expression* Let::copy() {
	return new Let(id_, e_value_->copy(), e_body_->copy());
}
