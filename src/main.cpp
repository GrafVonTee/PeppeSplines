#include <iostream>
#include <vector>
#include <cmath>
#include "splines.h"
#include "writer.h"
#include "parser.h"

const long double eps = 1e-3;
const int c_steps = 1e3;

ArrayPoint GetArrange(long double fromV, long double toV) {
    ArrayPoint newArrange;
    newArrange.reserve(c_steps);
    for (long double xi = fromV; xi <= toV; xi += (toV - fromV) * eps) {
        Point p = {xi, 0};
        newArrange.push_back(p);

    }
    return newArrange;
}

int main() {
    // Read and Parse Critical Points
    ArrayPoint firstSpline = ParsePoints(GetStringFromFile("../Input and tests/1.txt"));
    ArrayPoint secondSpline = ParsePoints(GetStringFromFile("../Input and tests/2.txt"));

    // Initialize Splines
    ArrayPoint newFirstSpline = GetArrange(-30, 10);//fmaxl(firstSpline[0].x, secondSpline[0].x),
                                           //fminl(firstSpline.back().x, secondSpline.back().x));
    ArrayPoint newSecondSpline = GetArrange(-30, 10);//fmaxl(firstSpline[0].x, secondSpline[0].x),
                                            //fminl(firstSpline.back().x, secondSpline.back().x));

    // Build Splines
    CreateSpline(firstSpline, newFirstSpline);
    CreateSpline(secondSpline, newSecondSpline);

    // Write Values into Files
    WritePointsIntoFile(newFirstSpline, "../Input and tests/1.out");
    WritePointsIntoFile(newSecondSpline, "../Input and tests/2.out");

    return 0;
}
