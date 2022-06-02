//
// Created by grafvontee on 28/05/22.
//
#include <cmath>
#include <vector>
#include "splines.h"

long double GetH(std::vector<Point> values, int index){
    if (index == 0)
        index += 1;
    return (values[index].x - values[index - 1].x);
}

Sweeps GetSweeps(std::vector<Point> values, int index) {
    Sweeps swp;
    swp.F = (values[index + 1].y - values[index].y) / GetH(values, index + 1)
            - values[index].y / GetH(values, index);
    if (index > 0)
        swp.F += (values.at(index - 1).y) / GetH(values, index);
    swp.A = GetH(values, index)/6;
    swp.B = (GetH(values, index) + GetH(values, index + 1))/3;
    swp.C = GetH(values, index + 1)/6;
    return swp;
}

long double GetAlpha(std::vector<Point> values, int index){
    Sweeps swp;
    swp = GetSweeps(values, index - 1);
    if(index == 1)
        return (-swp.C)/swp.B;
    return (-swp.C)/(swp.A * GetAlpha(values, index - 1) + swp.B);
}

long double GetBeta(std::vector<Point> values, int index){
    Sweeps swp;
    swp = GetSweeps(values, index - 1);
    if(index == 1)
        return swp.F/swp.B;
    return (swp.F - swp.A * GetBeta(values, index - 1))
        / (swp.A * GetAlpha(values, index - 1) + swp.B);
}
long double GetGamma(std::vector<Point> values, int index){
    if(index == 0 || index == values.size() - 1)
        return 0;
    if(index == 1 || index == values.size() - 2) {
        Sweeps swp = GetSweeps(values, index);
        return (swp.F - swp.A * GetBeta(values, index))/(swp.A * GetAlpha(values, index) + swp.B);
    }
    return GetAlpha(values, index + 1) * GetGamma(values, index + 1)
        + GetBeta(values, index + 1);
}

void CreateSpline(const std::vector<Point> &origValues, std::vector<Point> &newValues) {
    int i = 0;
    for (int j = 0; j < newValues.size(); ++j){
        long double x = newValues[j].x;
        while ((i < (origValues.size() - 2))
            && !((origValues[i].x <= x) && (x <= origValues[i + 1].x))
            && (x >= origValues[i].x)) {
            i += 1;
        }
        long double prt1 = (origValues[i + 1].x - x) / GetH(origValues, i + 1);
        long double prt2 = (x - origValues[i].x) / GetH(origValues, i + 1);
        long double prt3 = (powl(origValues[i + 1].x - x, 3)
                - powl(GetH(origValues, i + 1), 2) * (origValues[i + 1].x - x))
                        / (6 * GetH(origValues, i + 1));
        long double prt4 = (powl(x - origValues[i].x, 3)
                - powl(GetH(origValues, i + 1), 2) * (x - origValues[i].x))
                        / (6 * GetH(origValues, i + 1));
        newValues[j].y = origValues[i].y * prt1
                + origValues[i + 1].y * prt2
                + GetGamma(origValues, i) * prt3
                + GetGamma(origValues, i + 1) * prt4;
    }
}
