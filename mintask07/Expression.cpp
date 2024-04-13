#include <cmath>
#include <string>

using namespace std;

class Expression {
  public:
    virtual Expression *diff(string var) = 0;

    virtual string getString() = 0;
    virtual Expression *copy() = 0;

    virtual ~Expression() {
    }
};

class Binary : public Expression {
  protected:
    Expression *right_;
    Expression *left_;

  public:
    Binary(Expression *right, Expression *left) : right_(right), left_(left) {
    }

    virtual ~Binary() {
        delete right_;
        delete left_;
    }
};

class Unary : public Expression {
  protected:
    Expression *expr_;

  public:
    Unary(Expression *expr) : expr_(expr) {
    }

    virtual ~Unary() {
        delete expr_;
    }
};

class Add : public Binary {
  public:
    Add(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Add *copy() {
        Expression *newRight = right_->copy();
        Expression *newLeft = left_->copy();
        return new Add(newRight, newLeft);
    }

    virtual Expression *diff(string var) {
        return new Add(right_->diff(var), left_->diff(var));
    }

    virtual string getString() {
        return "(" + right_->getString() + " + " + left_->getString() + ")";
    }
};

class Sub : public Binary {
  public:
    Sub(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Sub *copy() {
        Expression *newRight = right_->copy();
        Expression *newLeft = left_->copy();
        return new Sub(newRight, newLeft);
    }

    virtual Expression *diff(string var) {
        return new Sub(right_->diff(var), left_->diff(var));
    }

    virtual string getString() {
        return "(" + right_->getString() + " - " + left_->getString() + ")";
    }
};

class Mult : public Binary {
  public:
    Mult(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Mult *copy() {
        Expression *newRight = right_->copy();
        Expression *newLeft = left_->copy();
        return new Mult(newRight, newLeft);
    }

    virtual Expression *diff(string var) {
        return new Add(new Mult(right_->diff(var), left_->copy()),
                       new Mult(right_->copy(), left_->diff(var)));
    }

    virtual string getString() {
        return right_->getString() + " * " + left_->getString();
    }
};

class Div : public Binary {
  public:
    Div(Expression *right, Expression *left) : Binary(right, left) {
    }

    virtual Div *copy() {
        Expression *newRight = right_->copy();
        Expression *newLeft = left_->copy();
        return new Div(newRight, newLeft);
    }

    virtual Expression *diff(string var) {
        return new Div(new Sub(new Mult(right_->diff(var), left_->copy()),
                               new Mult(right_->copy(), left_->diff(var))),
                       new Mult(left_->copy(), left_->copy()));
    }

    virtual string getString() {
        return "(" + right_->getString() + ") / (" + left_->getString() + ")";
    }
};

class Exponent : public Unary {
  public:
    Exponent(Expression *expr) : Unary(expr) {
    }

    virtual Exponent *copy() {
        Expression *newExpr = expr_->copy();
        return new Exponent(newExpr);
    }

    virtual Expression *diff(string var) {
        return new Mult(new Exponent(expr_->copy()), expr_->diff(var));
    }

    virtual string getString() {
        return "e ^ (" + expr_->getString() + ")";
    }
};

class Val : public Expression {
    double val_;

  public:
    Val(double val) : val_(val) {
    }

    virtual Val *copy() {
        return new Val(val_);
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

    virtual Var *copy() {
        return new Var(var_);
    }

    virtual Expression *diff(string var) {
        return new Val(var == var_);
    }

    virtual string getString() {
        return var_;
    }
};
