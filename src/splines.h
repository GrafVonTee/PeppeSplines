#pragma once

struct Point {
    long double x, y;
};

struct Sweeps {
    long double A, B, C, F;
};

typedef std::vector<Point> ArrayPoint;

void CreateSpline(const std::vector<Point> &origValues, std::vector<Point> &newValues);
long double GetH(std::vector<Point> values, int index);
long double GetAlpha(std::vector<Point>, int index);
long double GetBeta(std::vector<Point>, int index);
long double GetGamma(std::vector<Point>, int index);
Sweeps GetSweeps(std::vector<Point> values, int index);