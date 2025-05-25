#include "Call.h"

Call::Call(Expression* f_exp, Expression* arg_exp) : f_exp_(f_exp), arg_exp_(arg_exp) {
}

Call::operator std::string() const {
    return "(call " + static_cast<std::string>(*f_exp_) + " in " +
           static_cast<std::string>(*arg_exp_) + ")";
}

Expression* Call::eval(std::map<std::string, Expression*> env) {
    Expression* f_exp = f_exp_->eval(env);
    Function* func = dynamic_cast<Function*>(f_exp_->eval(env));
    if (func == nullptr) {
        throw ExpressionException("Can't call no function!");
    }
    Expression* arg = arg_exp_->eval(env);
    env.insert({func->id_, arg});
    Expression* result = func->e_body_->eval(env);
    delete arg;
    delete f_exp;
    delete func;
    return result;
}

Call::~Call() {
    if (f_exp_) {
        delete f_exp_;
    }
    if (arg_exp_) {
        delete arg_exp_;
    }
}

Expression* Call::copy() {
    return new Call(f_exp_->copy(), arg_exp_->copy());
}
