#include <iostream>
#include <ostream>
#include <string>
#include <variant>

using namespace std;

class Expression {
  public:
    virtual Expression *diff(string var) {
        return nullptr;
    }

    virtual string getString() {
        return "";
    }
};

class Binary : public Expression {
    Expression *right_;
    Expression *left_;

  public:
    Binary(Expression *right, Expression *left) : right_(right), left_(left) {
    }

    Expression *right() {
        return right_;
    }

    Expression *left() {
        return left_;
    }
};

class Unary : public Expression {
    Expression *expr_;

  public:
    Unary(Expression *expr) : expr_(expr) {
    }

    Expression *expr() {
        return expr_;
    }
};

class Add : public Binary {
  public:
    Add(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Expression *diff(string var) {
        return new Add(right()->diff(var), left()->diff(var));
    }

    virtual string getString() {
        return "(" + right()->getString() + " + " + left()->getString() + ")";
    }
};

class Sub : public Binary {
  public:
    Sub(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Expression *diff(string var) {
        return new Sub(right()->diff(var), left()->diff(var));
    }

    virtual string getString() {
        return "(" + right()->getString() + " - " + left()->getString() + ")";
    }
};

class Mult : public Binary {
  public:
    Mult(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Expression *diff(string var) {
        return new Add(new Mult(right()->diff(var), left()), new Mult(right(), left()->diff(var)));
    }

    virtual string getString() {
        return right()->getString() + " * " + left()->getString();
    }
};

class Div : public Binary {
  public:
    Div(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Expression *diff(string var) {
        return new Div(
            new Sub(new Mult(right()->diff(var), left()), new Mult(right(), left()->diff(var))),
            new Mult(left(), left()));
    }

    virtual string getString() {
        return "(" + right()->getString() + ") / (" + left()->getString() + ")";
    }
};

class Exponent : public Unary {
  public:
    Exponent(Expression *expr) : Unary(expr) {
    }

    virtual Expression *diff(string var) {
        return new Mult(expr(), expr()->diff(var));
    }

    virtual string getString() {
        return "e ^ (" + expr()->getString() + ")";
    }
};

class Val : public Expression {
    double val_;

  public:
    Val(double val) : val_(val) {
    }

    virtual Expression *diff(string var) {
        return new Val(0);
    }

    virtual string getString() {
        return to_string(val_);
    }
};

class Var : public Expression {
    string var_;

  public:
    Var(string var) : var_(var) {
    }

    virtual Expression *diff(string var) {
        return new Val(var == var_);
    }

    virtual string getString() {
        return var_;
    }
};

int main() {
    Expression *e = new Add(new Var("x"), new Mult(new Val(10), new Var("y")));
    Expression *res1 = e->diff("x");
    cout << res1->getString() << "\n";
    Expression *res2 = e->diff("y");
    cout << res2->getString() << "\n";
    return 0;
}
