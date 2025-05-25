#include "If.h"

If::If(Expression* e1, Expression* e2, Expression* e_then, Expression* e_else)
    : e1_(e1), e2_(e2), e_then_(e_then), e_else_(e_else) {
}

If::operator std::string() const {
    return "(if " + static_cast<std::string>(*e1_) + " " + static_cast<std::string>(*e2_) +
           " then " + static_cast<std::string>(*e_then_) + " else " +
           static_cast<std::string>(*e_else_) + ")";
}

Expression* If::eval(std::map<std::string, Expression*> env) {
    Expression* value_1 = e1_->eval(env);
    Expression* value_2 = e2_->eval(env);
    bool result = value_1->get_value() > value_2->get_value();
    delete value_1;
    delete value_2;
    if (result) {
        return e_then_->eval(env);
    } else {
        return e_else_->eval(env);
    }
}

If::~If() {
    if (e1_) {
        delete e1_;
    }
    if (e2_) {
        delete e2_;
    }
    if (e_then_) {
        delete e_then_;
    }
    if (e_else_) {
        delete e_else_;
    }
}

Expression* If::copy() {
    return new If(e1_->copy(), e2_->copy(), e_then_->copy(), e_else_->copy());
}
