#include <climits>
#include <vector>
#include <cmath>
#include "splines.h"
#include "intersection.h"

ArrayPoints GetArrange(long double fromV, long double toV, long int steps) {
    ArrayPoints newArrange;
    newArrange.reserve(steps);
    for (long double xi = fromV; xi <= toV; xi += (toV - fromV) * 1.0/steps) {
        Point p = {xi, 0};
        newArrange.push_back(p);
    }
    return newArrange;
}

ArrayPoints GetLocalCentralDerivative(const ArrayPoints &orig) {
    ArrayPoints derivative;
    derivative.reserve(orig.size() - 2);
    for (int i = 1; i < orig.size() - 1; ++i) {
        Point p = { orig[i].x, (orig[i+1].y - orig[i-1].y)/(orig[i+1].x - orig[i-1].x) };
        derivative.push_back(p);
    }
    return derivative;
}

int FindRootIndex(const ArrayPoints &spline) {
    for (int i = 0; i < spline.size() - 1; ++i)
        if (spline[i].y * spline[i+1].y <= 0)
            return i;
    return -1;
}

Point FindIntersection(
        const ArrayPoints &spline1,
        const ArrayPoints &spline3,
        int rootIndex,
        long double eps)
{
    ArrayPoints spline1Segment = { spline1[rootIndex], spline1[rootIndex + 1] };
    ArrayPoints spline3Segment = { spline3[rootIndex], spline3[rootIndex + 1] };
    long double a = spline1[rootIndex - 1].x;
    long double b = spline1[rootIndex + 1].x;

    ArrayPoints newMiniSpline1 = GetArrange(a, b, (int)(1/eps));
    ArrayPoints newMiniSpline3 = GetArrange(a, b, (int)(1/eps));

    CreateSpline(spline1Segment, newMiniSpline1);
    CreateSpline(spline3Segment, newMiniSpline3);

    Point rootPoint = {INT_MIN, INT_MIN};
    for (int i = 0; i < newMiniSpline3.size(); ++i)
        if (fabsl(newMiniSpline3[i].y) < fabsl(newMiniSpline3[i+1].y))
            rootPoint = { newMiniSpline1[i].x, newMiniSpline1[i].y };

    return rootPoint;
}

long double GetDistance(Point p1, Point p2) {
    return sqrtl( powl(p1.x - p2.x, 2) + powl(p1.y - p2.y, 2) );
}

ArrayPoints FindMinimalDistance(
        const ArrayPoints &spline1,
        const ArrayPoints &spline2,
        const ArrayPoints &spline3,
        long double epsilon)
{
    int extremumIndex = -1;

    ArrayPoints deriv3 = GetLocalCentralDerivative(spline3);
    ArrayPoints der_der3 = GetLocalCentralDerivative(deriv3);

    for (int i = 0; i < deriv3.size() - 1; ++i)
        if ((deriv3[i].y * deriv3[i+1].y <= 0) && (der_der3[i].y > 0))
            extremumIndex = i;

    ArrayPoints result;

    if (extremumIndex != -1) {
        Point intersect1And3Der = FindIntersection(spline1, deriv3, extremumIndex, epsilon);
        Point intersect2And3Der = FindIntersection(spline2, deriv3, extremumIndex, epsilon);
        result.push_back(intersect1And3Der);
        result.push_back(intersect2And3Der);

    } else {
        if (fabsl(spline3[0].y) < fabsl(spline3[spline3.size() - 1].y)) {
            result.push_back(spline1[0]);
            result.push_back(spline2[0]);
        } else {
            result.push_back(spline1[spline1.size() - 1]);
            result.push_back(spline2[spline2.size() - 1]);
        }
    }
    return result;
}

ArrayPoints FindDistanceOrIntersection(const ArrayPoints &spline1, const ArrayPoints &spline2,
                                      long double start, long double end, long double epsilon) {
    ArrayPoints spline3;
    spline3.reserve(spline1.size());
    for (int i = 0; i < spline1.size(); ++i) {
        Point p = {spline1[i].x, spline1[i].y - spline2[i].y};
        spline3.push_back(p);
    }
    int rootIndex = FindRootIndex(spline3);
    ArrayPoints somethingBetweenSplines;
    if (rootIndex != -1)
        somethingBetweenSplines
            .push_back(FindIntersection(spline1, spline3, rootIndex, epsilon));
    else
        somethingBetweenSplines = FindMinimalDistance(spline1, spline2, spline3, epsilon);

    return somethingBetweenSplines;
}