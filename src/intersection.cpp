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
/*
ArrayPoints FindMinimalDistance(const ArrayPoints &spline3) {
    int extremumIndex = -1;

    ArrayPoints deriv = GetLocalCentralDerivative(spline3);
    ArrayPoints der_der = GetLocalCentralDerivative(deriv);

    for (int i = 0; i < deriv.size() - 1; ++i)
        if ((deriv[i].y * deriv[i+1].y < 0) && (der_der[i].y > 0))
            extremumIndex = i;

    // Start Recoding Here

    distances = []
    distances += [abs(y01[0] - y02[0])]
    distances += [abs(y01[len(y01) - 1] - y02[len(y02) - 1])]

    if is_extrem:

        x_ap = [x0[extrem_i], x0[extrem_i + 1]]

    y_ap_1 = [y01[extrem_i], y01[extrem_i + 1]]
    y_ap_2 = [y02[extrem_i], y02[extrem_i + 1]]
    y_ap_d_3 = [y03_d[extrem_i], y03_d[extrem_i + 1]]

    a = x0[extrem_i - 1]
    b = x0[extrem_i + 1]

    x1, y1 = intersection(a, b, eps, x_ap, y_ap_1, y_ap_d_3)
    x2, y2 = intersection(a, b, eps, x_ap, y_ap_2, y_ap_d_3)
    distances += [abs(y1 - y2)]

    plt.vlines(x1, y1, y2, label="Min distance", color='red')
    plt.plot(x1, y1, 'go', label='P1')
    plt.plot(x1, y2, 'bo', label='P2')

    print("Min distance =", min(distances))
    print("Points of distance:\n"
          "P1: ({0}, {1})\n"
          "P2: ({2}, {3})".format
            (x1, y1, x2, y2))
    else:
    if min(distances) == distances[0]:
    plot_i = 0
    plot_x = x0[plot_i]
    else:
    plot_i = len(x0) - 1
    plot_x = x0[plot_i]

    plt.vlines(plot_x, y01[plot_i], y02[plot_i], label="Min distance", color='red')
    plt.plot(plot_x, y01[plot_i], 'go', label="P1")
    plt.plot(plot_x, y02[plot_i], 'bo', label="P2")

    print("Min distance =", min(distances))
    print("Points of distance:\n"
          "P1: ({0}, {1})\n"
          "P2: ({0}, {2})".format
            (plot_x, y01[plot_i], y02[plot_i]))
}
*/

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
    // else
    //    somethingBetweenSplines = FindMinimalDistance();

    return somethingBetweenSplines;
}