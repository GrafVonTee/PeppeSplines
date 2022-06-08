from operations import do_operations


def get_points_from_file(file, num):
    f = open(file, "r").readlines()
    M = [m.split(",") for m in f][num]
    X, Y = [], []
    for m in M:
        if m == " ":
            continue
        x, y = m.split()
        X += [float(x)]
        Y += [float(y)]
    return X, Y


def print_points(X, Y):
    for i in range(len(X)):
        print("({0}, {1})".format(X[i], Y[i]))
    print('\n')


def main():
    # a, b = 0, 12  # intersection
    a, b = -5, 5  # min distance using extremum
    # a, b = -10, 0  # min distance using boarder case

    # Data:
    h = 1e-3

    X1, Y1 = get_points_from_file('Input and tests/input', 0)
    X2, Y2 = get_points_from_file('Input and tests/input', 1)

    print('First spline:')
    print_points(X1, Y1)

    print('Second spline:')
    print_points(X2, Y2)

    do_operations(X1, Y1, X2, Y2, h, a, b)


if __name__ == "__main__":
    main()
