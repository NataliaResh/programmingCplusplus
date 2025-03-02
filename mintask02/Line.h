#pragma once
#include <cmath>
#include <optional>
#include "Point.h"

using namespace std;

class Line {
    double a_;
    double b_;
    double c_;

    static double roundCoeff(double x);

    void roundCoeffs();

  public:
    static optional<Line> createLineFromPoints(const Point &m, const Point &n);

    static optional<Line> createLineFromCoeffs(double a, double b, double c);
    double a() const;

    double b() const;

    double c() const;

    Line(const Point &m, const Point &n);

    Line(double a, double b, double c);

    Line(double k, double m);

    bool operator==(const Line&line);

    bool isParallel(const Line &line);

    optional<Point> intersection(const Line& line);

    Line perpendicular(const Point& p);
};
