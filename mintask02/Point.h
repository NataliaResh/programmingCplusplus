#pragma once
#include <cmath>

using namespace std;

static double const e = 1e+5;
 
struct Point {
  private:
    double x_;
    double y_;

    static double roundCoeff(double x);

    void roundCoeffs();

  public:
        
    Point(double x, double y);

    const double& x() const;

    const double& y() const;

    bool operator==(const Point& p) const;

    bool operator!=(const Point& p) const;
};
