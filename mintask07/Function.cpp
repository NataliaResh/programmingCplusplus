#include "Function.h"

Function::Function(std::string id, Expression* e_body) : id_(id), e_body_(e_body) {
}

Function::operator std::string() const {
    return "(function " + id_ + " " + static_cast<std::string>(*e_body_) + ")";
}

Expression* Function::eval() {
    return this;
}

Expression* Function::eval(std::map<std::string, Expression*> env) {
    return this;
}

Function::~Function() {
    if (e_body_) {
        delete e_body_;
    }
}

Expression* Function::copy() {
	return new Function(id_, e_body_->copy());
}
