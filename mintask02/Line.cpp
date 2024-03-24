#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>

using namespace std;

const static double e = 1e+5;

struct Point {
    double x;
    double y;

    static double roundCoeff(double x) {
        return round(x * e) / e;
    }

    void roundCoeffs() {
        x = roundCoeff(x);
        y = roundCoeff(y);
    }

    Point(double x, double y) : x(x), y(y) {
        roundCoeffs();
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point &p) const {
        return !(*this == p);
    }
};

class Line {

    double a_;
    double b_;
    double c_;

    static double roundCoeff(double x) {
        return round(x * e) / e;
    }

    void roundCoeffs() {
        a_ = roundCoeff(a_);
        b_ = roundCoeff(b_);
        c_ = roundCoeff(c_);
    }

  public:
    const double &a() const {
        return a_;
    }

    const double &b() const {
        return b_;
    }

    const double &c() const {
        return c_;
    }

    Line(Point &m, Point &n) {
        assert(m != n);
        if (n.y == m.y) {
            a_ = (n.y - m.y) / (m.x - n.x);
            b_ = 1;
            c_ = -a_ * m.x - m.y;
        } else {
            a_ = 1;
            b_ = (m.x - n.x) / (n.y - m.y);
            c_ = -b_ * m.y - m.x;
        }
        roundCoeffs();
    }

    Line(double a, double b, double c) {
        assert(a != 0 || b != 0);
        a_ = a;
        b_ = b;
        c_ = c;
        roundCoeffs();
    }

    Line(double k, double m) {
        a_ = k;
        b_ = -1;
        c_ = m;
        roundCoeffs();
    }

    bool operator==(const Line &line) {
        return isParallel(line) && b_ * line.c_ == c_ * line.b_;
    }

    bool isParallel(const Line &line) {
        return a_ * line.b_ == b_ * line.a_;
    }

    optional<Point> intersection(const Line &line) {
        if (isParallel(line)) {
            return nullopt;
        }
        double x = 0, y;
        if (a_ == 0) {
            y = -c_ / b_;
        } else {
            y = (line.a_ * c_ - line.c_ * a_) / (line.b_ * a_ - line.a_ * b_);
            x = (-b_ * y - c_) / a_;
        }
        return Point(x, y);
    }

    Line *perpendicular(const Point &p) {
        double a = -b_;
        double b = a_;
        double c = -(a * p.x + b * p.y);
        return new Line(a, b, c);
    }
};
