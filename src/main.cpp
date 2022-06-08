#include <iostream>
#include <vector>
#include <cmath>
#include "splines.h"
#include "writer.h"
#include "parser.h"
#include "intersection.h"

const long double eps = 1e-3;
const long int c_steps = 1e3;

void PrintPoints(ArrayPoints arr) {
    for (auto a : arr)
        printf("(%Lf; %Lf), ", a.x, a.y);
    printf("\n");
}

int main() {
    // Define new Variables
    long double a(-30), b(30);

    // Read and Parse Critical Points
    ArrayPoints firstSpline = ParsePoints(GetStringFromFile("../Input and tests/1.txt"));
    ArrayPoints secondSpline = ParsePoints(GetStringFromFile("../Input and tests/2.txt"));

    // Initialize Splines
    ArrayPoints newFirstSpline = GetArrange(a, b, c_steps);//fmaxl(firstSpline[0].x, secondSpline[0].x),
                                           //fminl(firstSpline.back().x, secondSpline.back().x));
    ArrayPoints newSecondSpline = GetArrange(a, b, c_steps);//fmaxl(firstSpline[0].x, secondSpline[0].x),
                                            //fminl(firstSpline.back().x, secondSpline.back().x));

    // Build Splines
    CreateSpline(firstSpline, newFirstSpline);
    CreateSpline(secondSpline, newSecondSpline);

    // Write Values into Files
    WritePointsIntoFile(newFirstSpline, "../Input and tests/1.out");
    WritePointsIntoFile(newSecondSpline, "../Input and tests/2.out");

    ArrayPoints minimalDistance = FindDistanceOrIntersection(
            newFirstSpline,
            newSecondSpline,
            a, b, eps);

    PrintPoints(minimalDistance);
    return 0;
}
