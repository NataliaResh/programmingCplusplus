#include <exception>
#include <string>

class ExpressionException : public std::exception {
  private:
    std::string message_;

  public:
    ExpressionException(std::string msg);
    const char* what() const throw();
};
