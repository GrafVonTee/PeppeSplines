import matplotlib.pyplot as plt
import numpy as np
from Spline_2 import spline

'''
def shit_finding_method(points):

    if len(points) == 1:
        print('Point of intersection: ', points[0])
    else:
        for i in range(1, len(points)):
            if abs(points[i - 1][1] - points[i][1]) < 1:
                continue
            else:
                print('Point of intersection: ', points[i - 1])
            if i == len(points) - 1:
                if abs(points[i - 1][1] - points[len(points) - 1][1]) < 1:
                    continue
                else:
                    print('Point of intersection: ', points[i])
'''


def draw_graph(curves_set, a, b, h):

    plt.figure(figsize=(7, 7))

    # Spline_1
    cur1_X = curves_set[0][0]
    cur1_x0 = np.arange(a, b + h, h)
    cur1_Y = curves_set[0][1]
    cur1_y0 = spline(cur1_X, cur1_Y, cur1_x0)
    plt.plot(cur1_x0, cur1_y0, label='Spline_1', color='black')

    # Spline_2
    cur2_X = curves_set[1][0]
    cur2_x0 = np.arange(a, b + h, h)
    cur2_Y = curves_set[1][1]
    cur2_y0 = spline(cur2_X, cur2_Y, cur2_x0)
    plt.plot(cur2_x0, cur2_y0, label='Spline_2', color='blue')

    points = []
    for i in range(len(cur1_y0)):
        if round(cur1_y0[i], 1) == round(cur2_y0[i], 1) \
                and round(cur1_x0[i], 1) == round(cur2_x0[i], 1):
            plt.plot(cur1_x0[i], cur1_y0[i], 'ro')
            points.append([cur1_x0[i], cur2_y0[i]])

    # shit_finding_method(points)

    plt.title('Cubic Spline Interpolation')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.grid()
    plt.legend()
    plt.show()
