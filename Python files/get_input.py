from io import StringIO
import numpy as np
from os import getcwd


def get_points(curve):

    def sort_x(x, y):
        for i in range(len(x)):
            for j in range(len(x) - i - 1):
                if x[j] > x[j + 1]:
                    x[j], x[j + 1] = x[j + 1], x[j]
                    y[j], y[j + 1] = y[j + 1], y[j]
        return x, y

    x_points, y_points = [], []

    for i in range(len(curve)):
        for j in range(2):
            if j == 0:
                x_points.append(curve[i][j])
            else:
                y_points.append(curve[i][j])
    points = sort_x(x_points, y_points)
    return points


def get_curves():

    def parse_str():
        file = open(getcwd() + '/Input and tests/input.txt', 'r')  # Write a path to file
        lines = file.readlines()
        file.close()
        for i in range(2):
            lines[i] = lines[i].replace(',', '\n', lines[i].count(','))
        return lines

    line = parse_str()
    curve_1 = np.loadtxt(StringIO(line[0]))
    curve_2 = np.loadtxt(StringIO(line[1]))

    print('\nCurve №1\n', curve_1)
    print('\nCurve №2\n', curve_2, '\n')

    curve1_points = get_points(curve_1)
    curve2_points = get_points(curve_2)

    return curve1_points, curve2_points
