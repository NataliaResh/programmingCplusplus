#pragma once
#include "Add.h"
#include "Call.h"
#include "Expression.h"
#include "Function.h"
#include "If.h"
#include "Let.h"
#include "Val.h"
#include "Var.h"
#include <stack>
#include <string>

class Parser {
  private:
    std::string get_word(std::string& str, size_t& i);
    size_t get_sub_expression(std::string& str, size_t start);
    Expression* parse_impl(std::string& str, size_t start, size_t end);
    Expression* parse_add(std::string& str, size_t start, size_t end);
    Expression* parse_if(std::string& str, size_t start, size_t end);
    Expression* parse_let(std::string& str, size_t start, size_t end);
    Expression* parse_function(std::string& str, size_t start, size_t end);
    Expression* parse_call(std::string& str, size_t start, size_t end);
    std::pair<Expression*, Expression*> parse_two_expr(std::string& str, size_t& start);

  public:
    Expression* parse(std::string& str);
};
