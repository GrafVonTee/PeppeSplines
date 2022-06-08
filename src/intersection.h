#pragma once

ArrayPoints GetArrange(long double fromV, long double toV, long int steps);
ArrayPoints GetLocalCentralDerivative(const ArrayPoints &orig);
ArrayPoints FindDistanceOrIntersection(const ArrayPoints &spline1, const ArrayPoints &spline2,
                                       long double start, long double end, long double epsilon);
Point FindIntersection(
        const ArrayPoints &spline1,
        const ArrayPoints &spline3,
        int rootIndex,
        long double eps);

ArrayPoints FindMinimalDistance();
