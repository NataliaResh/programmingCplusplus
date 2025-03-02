#include "Point.h"

double Point::roundCoeff(double x) {
  return round(x * e) / e;
}

void Point::roundCoeffs() {
  x_ = roundCoeff(x_);
  y_ = roundCoeff(y_);
}

Point::Point(double x, double y): x_(x), y_(y) {
  roundCoeffs();
}

double const &Point::x() const {
  return x_;
}

double const &Point::y() const {
  return y_;
}

bool Point::operator==(const Point& p) const {
  return x_ == p.x_ && y_ == p.y_;
}

bool Point::operator!=(const Point& p) const {
  return !(*this == p);
}
