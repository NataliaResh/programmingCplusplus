#include <cmath>

const static double e = 1e+5;

class Point {
    double x_;
    double y_;

    static double roundCoeff(double x) {
        return round(x * e) / e;
    }

    void roundCoeffs() {
        x_ = roundCoeff(x_);
        y_ = roundCoeff(y_);
    }

  public:
    const double &x() const {
        return x_;
    }

    const double &y() const {
        return y_;
    }

    Point(double x, double y) {
        x_ = x;
        y_ = y;
        roundCoeffs();
    }

    bool operator==(const Point &p) {
        return x_ == p.x_ && y_ == p.y_;
    }

    bool operator!=(const Point &p) {
      return !(*this == p);
    }
};
