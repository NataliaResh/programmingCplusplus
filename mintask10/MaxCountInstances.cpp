#include "MaxCountInstances.h"

MaxCountInstances::MaxCountInstances(size_t limit) {
    msg_ = "Try to create more than ";
    msg_ += std::to_string(limit);
    msg_ += " instances of class!";
}
