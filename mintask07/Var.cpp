#include "Var.h"

Var::Var(std::string id) : id_(id) {
}

Var::operator std::string() const {
    return "(var " + id_ + ")";
}

Expression* Var::from_env(std::map<std::string, Expression*> env) {
    if (!env.empty() && env.find(id_) != env.end()) {
        return env.at(id_)->copy();
    }
    throw ExpressionException("There no variable " + id_ + " in current scope!");
}

Expression* Var::eval(std::map<std::string, Expression*> env) {
    return from_env(env);
}

Expression* Var::copy() {
    return new Var(id_);
}
