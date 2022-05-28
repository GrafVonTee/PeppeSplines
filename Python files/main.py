from get_input import get_curves
from drawing import draw_graph
import newton


def main():
    a, b = -30, 0
    h = 0.01
    curves_set = get_curves()
    draw_graph(curves_set, a, b, h)

    '''
        curves_set[0][0] - Curve's_1 x-points
        curves_set[0][1] - Curve's_1 y-points
        curves_set[1][0] - Curve's_1 x-points
        curves_set[1][1] - Curve's_2 y-points
    '''


if __name__ == "__main__":
    # newton.main_newtone()
    main()
