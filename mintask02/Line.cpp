#include "Line.h"

optional<Line> Line::createLineFromPoints(const Point &m, const Point &n) {
    if (m == n) {
        return nullopt;
    }
    return Line(m, n);
}

optional<Line> Line::createLineFromCoeffs(double a, double b, double c) {
    if (a == 0 && b == 0) {
        return nullopt;
    }
    return Line(a, b, c);
}

double Line::roundCoeff(double x) {
    return round(x * e) / e;
}

void Line::roundCoeffs() {
    a_ = roundCoeff(a_);
    b_ = roundCoeff(b_);
    c_ = roundCoeff(c_);
}

// PR: why should we return const reference to double field?
// to avoid copying?
//It's easier to just return double, because there are no gain in memory
double Line::a() const {
    return a_;
}

double Line::b() const {
    return b_;
}

double Line::c() const {
    return c_;
}

Line::Line(const Point &m, const Point &n) {
    if (n.y() == m.y()) {
        a_ = (n.y() - m.y()) / (m.x() - n.x());
        b_ = 1;
        c_ = -a_ * m.x() - m.y();
    } else {
        a_ = 1;
        b_ = (m.x() - n.x()) / (n.y() - m.y());
        c_ = -b_ * m.y() - m.x();
    }
    roundCoeffs();
}

Line::Line(double a, double b, double c) : a_(a), b_(b), c_(c) {
    roundCoeffs();
}

Line::Line(double k, double m) : a_(k), c_(m) {
    b_ = -1;
    roundCoeffs();
}

bool Line::operator==(const Line &line) {
    return isParallel(line) && b_ * line.c_ == c_ * line.b_;
}

bool Line::isParallel(const Line &line) {
    return a_ * line.b_ == b_ * line.a_;
}

// Note: nice usage of optional! I like it)
optional<Point> Line::intersection(const Line &line) {
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

Line Line::perpendicular(const Point &p) {
    double a = -b_;
    double b = a_;
    double c = -(a * p.x() + b * p.y());
    return Line(a, b, c);
}
