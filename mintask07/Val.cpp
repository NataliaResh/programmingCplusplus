#include "Val.h"

Val::Val(int value) : value_(value) {
}

Expression* Val::eval(std::map<std::string, Expression*> env) {
    return new Val(value_);
}

Val::operator std::string() const {
    return "(val " + std::to_string(value_) + ")";
}

int Val::get_value() {
    return value_;
}

Val::~Val() {
}

Expression* Val::copy() {
    return new Val(value_);
}
