#pragma once
#include <string>

class MaxCountInstances : public std::exception {
    std::string msg_;

  public:
    MaxCountInstances(size_t limit);
};
