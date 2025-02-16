#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>

/*
PR: Summary

    So it is the great work once again, but I have some commentaries
    about consistency of 'const' modifier in methods signatures.
    Lets add where they to all places where they can be
    (actually it is one place and I left comment there)

    Also there is concern about error handling in constructor
    I suggest you to design new api using `std::optional`
*/

using namespace std;

const static double e = 1e+5;

// PR:
// maybe Point should have some private fields
// cause I can change the precision from the outside
// but your struct thinks that all numbers has only five digits after comma, 
// and this is invariant of your struct 
// this is the reason why your operator== is correct 
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
    // PR: why should we return const reference to double field?
    // to avoid copying?
    const double &a() const {
        return a_;
    }

    const double &b() const {
        return b_;
    }

    const double &c() const {
        return c_;
    }

    // PR: maybe n and m can be constant references?
    Line(Point &m, Point &n) {
        // PR: assertions it is kinda old way of error handling
        // we use them in C because we have no alternatives
        // but now we in C++)
        // Maybe we can redisign this part of code?
        // We still need to check that there is two different points
        // but should we do this check in the constructor? (hint: this is something about OOP)
        // You already used `std::optional` for handling errors
        // maybe we can use it somehow and for this situation?
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
        // PR: the same concern about asserts in constructors as above
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

    // Note: nice usage of optional! I like it)
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

    // PR: it is a bit strange to return pointer to Line here
    // I guess you try to avoid copying, but it is okay here to return Line by value
    // I mean you return Point by value in intersection method and it is okay) 
    Line *perpendicular(const Point &p) {
        double a = -b_;
        double b = a_;
        double c = -(a * p.x + b * p.y);
        return new Line(a, b, c);
    }
};
