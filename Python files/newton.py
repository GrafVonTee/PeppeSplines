from sympy import lambdify, symbols, cos, sin, pi
import numpy as np


def put(f, x, arg):
    f = lambdify(x, f)
    return f(*arg)


def jacobian(f, x):
    return np.matrix([[fi.diff(xi) for fi in f] for xi in x])


def mult_put(xf, x, args):
    return np.vectorize(lambda f: put(f, x, args))(xf)


def print_values(x, X):
    xX = [str(x[i]) + " = " + str(X[i]) for i in range(len(X))]
    print(*xX, sep=",\t ")


def newtone(xf, x, J, eps):
    X = np.array([z + 1 for z in np.zeros(len(x))])
    XF = mult_put(xf, x, X)
    iterations = 0
    while any(abs(xfi) > eps for xfi in XF):
        JX = mult_put(J, x, X) ** (-1)
        X -= (XF * JX).A1
        XF = mult_put(xf, x, X)
        iterations += 1

        print(str(iterations) + ")", end=" ")
        print_values(x, X)
    return X
