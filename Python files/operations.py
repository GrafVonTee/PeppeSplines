import numpy as np
import matplotlib.pyplot as plt
from Cubic_Splines import spline
from math import inf


def der_local(y0, h):
    vals = []
    for i in range(0, len(y0)-2):
        val = (y0[i+1] - y0[i])/h
        vals += [val]
    return vals


def intersection(a, b, h, x, y_1, y_3):
    x0 = np.arange(a, b+h, h)

    new_y_1 = spline(x, y_1, x0)
    new_y_3 = spline(x, y_3, x0)

    min_x, min_y = inf, inf
    for i in range(0, len(x0)-3):
        if abs(new_y_3[i]) < abs(new_y_3[i+1]):
            min_x = x0[i]
            min_y = new_y_1[i]
    return min_x, min_y


def do_operations(X1, Y1, X2, Y2, h, a, b):
    plt.figure(figsize=(7, 7))

    x0 = np.arange(a, b + h, h)

    y01 = spline(X1, Y1, x0)
    y02 = spline(X2, Y2, x0)
    y03 = []
    for i in range(len(y02)):
        y03.append(y01[i] - y02[i])

    plt.plot(x0, y01, label="Spline 1", color='green')
    plt.plot(x0, y02, label="Spline 2", color='blue')

    # plt.plot(x0, y03, label="Spline 1 - Spline 2", color='orange')

    root_i = 0
    is_root = False
    for i in range(len(y03) - 1):
        if y03[i] * y03[i + 1] < 0:
            root_i = i
            is_root = True

    eps = 1e-6

    if is_root:

        x_ap = [x0[root_i], x0[root_i+1]]
        y_ap_1 = [y01[root_i], y01[root_i+1]]
        y_ap_3 = [y03[root_i], y03[root_i+1]]

        a = x0[root_i - 1]
        b = x0[root_i + 1]

        x, y = intersection(a, b, eps, x_ap, y_ap_1, y_ap_3)
        print('Intersection point: ({0}, {1})'.format(x, y))
        plt.plot(x, y, 'ro', label='Intersection')

    else:
        extrem_i = 0
        is_extrem = False

        y03_d = der_local(y03, h)
        y03_d_d = der_local(y03_d, h)

        for i in range(len(y03_d) - 1):
            if y03_d[i] * y03_d[i + 1] < 0 and y03_d_d[i] > 0:
                extrem_i = i
                is_extrem = True

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

    plt.title("Cubic Spline Interpolation")
    plt.grid()
    plt.legend()
    plt.show()
