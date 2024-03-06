import math
import scipy as sp
import numpy as np
from matplotlib import pyplot as plt
import sympy
from sympy import lambdify, symbols, diff

def f(x):
    return math.exp(x) - 1/3 * (x ** 3) + 2 * x

def dfdx(x):
    return math.exp(x) - x ** 2 + 2

def d2fdx2(x):
    return math.exp(x) - 2 * x

bounds = [-2.5, -1]

def f_thrid(x):
    return x * math.atan(x) - 0.5 * math.log(1 + x**2)

def dfdx_thrid(x):
    return math.atan(x)


def review_func():
    result = sp.optimize.minimize_scalar(f, bounds=bounds)
    print(f"""
        minimize_scalar:
            x:      {result.x}   
            f(x):   {result.fun} 
    """)

    x0 = sum(bounds)/len(bounds)

    result =  sp.optimize.minimize(f, x0)
    print(f"""
        minimize:
            x:      {result.x[0]}   
            f(x):   {result.fun} 
    """)

    result = sp.optimize.fmin(f, x0)
    print(f"""
        fmin:
            x:      {result[0]}   
    """)

def create_plot(x, y, points=None, title="График"):
    plt.plot(x, y)
    if points:
        x_points, y_points = zip(*points)
        plt.scatter(x_points, y_points, color='red', label='точки')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(title)
    plt.grid(True)

    # plt.xlim(-5, 5)
    # plt.ylim(-2, 120)

    plt.legend()
    plt.show()

def create_data(f, bounds=bounds, n=1000):
    x, y = [], []
    step = (bounds[1] - bounds[0]) / n 
    for i in range(n):
        x.append(bounds[0] + i * step)
        y.append(f(bounds[0] + i * step))

    return {'x' : x, 'y' : y}

def bitwise_search(p, q, epsilon, f=f, bounds=bounds):
    [a, b] = bounds
    h = (b - a) / p

    iter_counter = 0
    f_counter = 0
    df_counter = 0

    points_data = []

    while h > epsilon:
        iter_counter += 1 
        x = a
        min_x = x
        min_f_x = f(x)

        points_data.append((min_x, min_f_x))

        f_counter += 1
        while x < b:
            x += h
            f_x = f(x)
            f_counter += 1
            if f_x < min_f_x:
                min_x = x
                min_f_x = f_x
        a = min_x - q * h
        b = min_x + q * h
        h *= q

    result = (a + b) / 2
    print(f"""
        Метод поразрядного поиска:
            x:            {result} 
            iter_counter: {iter_counter}
            f_counter:    {f_counter}
            df_counter:   {df_counter}
    """)
    return { 'result' : result, 'points_data' : points_data }

def golden_section(epsilon, f=f, bounds=bounds):
    [a, b] = bounds
    phi = (1 + 5**0.5) / 2 
    c = b - (b - a) / phi
    d = a + (b - a) / phi

    iter_counter = 0
    f_counter = 0
    df_counter = 0

    points_data = []

    while abs(c - d) > epsilon:
        iter_counter += 1
        f_counter += 2
        if f(c) < f(d):
            b = d
            points_data.append((b, f(b)))
        else:
            a = c
            points_data.append((a, f(a)))
        c = b - (b - a) / phi
        d = a + (b - a) / phi

    result = (a + b) / 2
    print(f"""
        Метод золотого сечения:
            x:            {result} 
            iter_counter: {iter_counter}
            f_counter:    {f_counter}
            df_counter:   {df_counter}
    """)
    return { 'result' : result, 'points_data' : points_data }

def chord_method(epsilon, max_iter=100_000):
    [a, b] = bounds

    iter_counter = 0
    f_counter = 0
    df_counter = 0

    points_data = []

    while abs(b - a) > epsilon:

        iter_counter += 1
        f_counter += 4
        df_counter += 2

        x = (a * f(b) - b * f(a)) / (f(b) - f(a))
        if dfdx(x) * dfdx(a) < 0:
            b = x
            points_data.append((b, f(b)))
        else:
            a = x
            points_data.append((a, f(a)))
    result = (a + b) / 2

    print(f"""
        Метод хорд:
            x:              {result}  
            Ɛ:              {epsilon}
            iter_counter:   {iter_counter}
            f_counter:      {f_counter}
            df_counter:     {df_counter}
    """)
    return { 'result' : result, 'points_data' : points_data }

def marquardt(f=f, dfdx=dfdx, bounds=bounds, tol=1e-4, max_iter=100_000, lam=0.01):
    x = np.array([2])

    iter_counter = 0
    f_counter = 0
    df_counter = 0

    points_data = []

    while iter_counter < max_iter:
        f_counter += 1
        df_counter += 1

        f_val = f(x)
        gradient = dfdx(x)

        if np.linalg.norm(gradient) < tol:
            break

        df_counter += 1
        hessian_approx = dfdx(x) + lam * np.eye(len(x))
        
        step = np.linalg.solve(hessian_approx, [-gradient])

        f_counter += 1
        x_new = x + step
        f_val_new = f(x_new)

        if f_val_new < f_val:
            lam /= 10
            x = x_new
        else:
            lam *= 10

        points_data.append((x_new, f_val_new))

        iter_counter += 1
    print(f"""
        Метод Марквардта:
            x:            {x[0]} 
            iter_counter: {iter_counter}
            f_counter:    {f_counter}
            df_counter:   {df_counter}
    """)

    return { 'result' : x, 'points_data' : points_data }

def broken_line_method(epsilon):
    x0 = sum(bounds)/len(bounds)

    iter_counter = 0
    f_counter = 0
    df_counter = 0

    points_data = []

    while True:
        iter_counter += 1
        f_counter += 2
        dfx = (f(x0 + epsilon) - f(x0 - epsilon)) / (2 * epsilon)
        alpha = 1
        new_x = x0 - alpha * dfx

        f_counter += 2
        while f(new_x) > f(x0):
            alpha /= 2
            new_x = x0 - alpha * dfx
        
        points_data.append((new_x, f(new_x)))

        if abs(new_x - x0) < epsilon:
            print(f"""
        Метод ломанных:
            x:            {new_x} 
            iter_counter: {iter_counter}
            f_counter:    {f_counter}
            df_counter:   {df_counter}
        """)
            return { 'result' : new_x, 'points_data' : points_data }
        x0 = new_x

def f_new(x):
    return math.exp(x) - 1 - x - x**2 / 2 - x**3 / 6

def main():
    
    # data = create_data()

    # print(data['x'], data['y']) 
    # review_func()
    
    epsilon = 1e-4

    # bitwise_search(100, 0.5, epsilon)
    # result = bitwise_search(100, 0.5, epsilon)['points_data']

    # golden_section(epsilon)
    # result = golden_section(epsilon)['points_data']

    # chord_method(epsilon)
    # result = chord_method(epsilon)['points_data']

    # marquardt(epsilon)
    # result = marquardt(epsilon)['points_data']

    # broken_line_method(epsilon)
    # result = broken_line_method(epsilon)['points_data']

    # create_plot(data['x'], data['y'], result)


    # for degree in range(1, 7):
    #     chord_method(10**(-1*degree))

    # create_plot([1, 2, 3, 4, 5, 6], [7, 166325, 166325, 166325, 166325, 166325])

    # bounds_new = [-5, 5]

    # data = create_data(f_new, bounds_new)

    # result = bitwise_search(100, 0.5, epsilon, f_new, bounds_new)['points_data']
    # result = golden_section(epsilon, f_new, bounds_new)['points_data']
    # create_plot(data['x'], data['y'], result)

    bounds_thrid = [-2, 2]

    data = create_data(f_thrid, bounds_thrid)
    result = marquardt(f_thrid, dfdx_thrid, bounds_thrid, 1e-4, 100, epsilon)['points_data']
    create_plot(data['x'], data['y'], result)



if __name__ == '__main__':
    main()


