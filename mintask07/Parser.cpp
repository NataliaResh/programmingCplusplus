#include "Parser.h"

Expression* Parser::parse(std::string& str) {
    return parse_impl(str, 0, str.size() - 1);
}

Expression* Parser::parse_impl(std::string& str, size_t start, size_t end) {
    if (str[0] != '(' || str[end] != ')') {
        throw ExpressionException("Incorrect string for parsing!");
    }
    ++start;
    std::string type = get_word(str, start);
    if (type == "val") {
        return new Val(std::stoi(str.substr(start, end - start)));
    } else if (type == "var") {
        return new Var(str.substr(start, end - start));
    } else if (type == "add") {
        return parse_add(str, start, end);
    } else if (type == "if") {
        return parse_if(str, start, end);
    } else if (type == "let") {
        return parse_let(str, start, end);
    } else if (type == "function") {
        return parse_function(str, start, end);
    } else if (type == "call") {
        return parse_call(str, start, end);
    }
    throw new std::exception();
}

Expression* Parser::parse_add(std::string& str, size_t start, size_t end) {
    std::pair<Expression*, Expression*> exprs = parse_two_expr(str, start);
    return new Add(exprs.first, exprs.second);
}

Expression* Parser::parse_if(std::string& str, size_t start, size_t end) {
    std::pair<Expression*, Expression*> exprs = parse_two_expr(str, start);
    ++start;
    std::string then_word = get_word(str, start);
    if (then_word != "then") {
        throw ExpressionException("Incorrect string for parsing!");
    }
    size_t end_then = get_sub_expression(str, start);
    Expression* e_then = parse_impl(str, start, end_then);
    if (str[end_then + 1] != ' ') {
        throw ExpressionException("Incorrect string for parsing!");
    }
    start = end_then + 2;
    std::string else_word = get_word(str, start);
    if (else_word != "else") {
        throw ExpressionException("Incorrect string for parsing!");
    }
    size_t end_else = get_sub_expression(str, start);
    if (end_else != end - 1) {
        throw ExpressionException("Incorrect string for parsing!");
    }
    Expression* e_else = parse_impl(str, start, end_else);
    return new If(exprs.first, exprs.second, e_then, e_else);
}

Expression* Parser::parse_let(std::string& str, size_t start, size_t end) {
    std::string id = get_word(str, start);
    std::string equality_word = get_word(str, start);
    if (equality_word != "=") {
        throw ExpressionException("Incorrect string for parsing!");
    }
    size_t end1 = get_sub_expression(str, start);
    if (str[end1 + 1] != ' ') {
        throw ExpressionException("Incorrect string for parsing!");
    }
    Expression* e1 = parse_impl(str, start, end1);
    start = end1 + 2;
    std::string in_word = get_word(str, start);
    if (in_word != "in") {
        throw ExpressionException("Incorrect string for parsing!");
   }
    size_t end2 = get_sub_expression(str, start);
    if (end2 != end - 1) {
        throw ExpressionException("Incorrect string for parsing!");
    }
    Expression* e2 = parse_impl(str, start, end2);
    return new Let(id, e1, e2);
}

Expression* Parser::parse_function(std::string& str, size_t start, size_t end) {
    std::string id = get_word(str, start);
    size_t end1 = get_sub_expression(str, start);
    if (str[end1 + 1] != ' ') {
        throw ExpressionException("Incorrect string for parsing!");
    }
    Expression* e1 = parse_impl(str, start, end1);
    if (end1 != end - 1) {
        throw ExpressionException("Incorrect string for parsing!");
    }
    return new Function(id, e1);
}

Expression* Parser::parse_call(std::string& str, size_t start, size_t end) {
    std::pair<Expression*, Expression*> exprs = parse_two_expr(str, start);
    return new Call(exprs.first, exprs.second);
}

std::pair<Expression*, Expression*> Parser::parse_two_expr(std::string& str, size_t& start) {
    size_t end1 = get_sub_expression(str, start);
    if (str[end1 + 1] != ' ') {
        throw ExpressionException("Incorrect string for parsing!");
    }
    Expression* e1 = parse_impl(str, start, end1);
    size_t end2 = get_sub_expression(str, end1 + 2);
    Expression* e2 = parse_impl(str, end1 + 2, end2);
    start = end2 + 1;
    return {e1, e2};
}

std::string Parser::get_word(std::string& str, size_t& i) {
    std::string ans = "";
    for (; str[i] != ' '; ++i) {
        ans += str[i];
    }
    ++i;
    return ans;
}

size_t Parser::get_sub_expression(std::string& str, size_t start) {
    std::stack<bool> stack;
    if (start >= str.size() || str[start] != '(') {
        throw ExpressionException("Incorrect string for parsing!");
     }
    stack.push(1);
    ++start;
    for (; !stack.empty() && start < str.size(); ++start) {
        if (str[start] == '(') {
            stack.push(1);
        } else if (str[start] == ')') {
            stack.pop();
        }
    }
    if (!stack.empty()) {
        throw ExpressionException("Incorrect string for parsing!");
    }
    return start - 1;
}
