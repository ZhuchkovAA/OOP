import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm

def f(x):
    f.count += 1
    x1, x2 = x
    return 100 * (x1 ** 2 - x2) ** 2 + (x1 - 1) ** 2
f.count = 0

def gradient_f(x):
    gradient_f.count += 1
    x1, x2 = x
    df_dx1 = 400 * x1 * (x1 ** 2 - x2) + 2 * (x1 - 1)
    df_dx2 = -200 * (x1 ** 2 - x2)
    return np.array([df_dx1, df_dx2])
gradient_f.count = 0

def hessian_f(x):
    hessian_f.count += 1
    x1, x2 = x
    d2f_dx1dx1 = 1200 * x1 ** 2 - 400 * x2 + 2
    d2f_dx1dx2 = -400 * x1
    d2f_dx2dx2 = 200
    return np.array([[d2f_dx1dx1, d2f_dx1dx2], [d2f_dx1dx2, d2f_dx2dx2]])
hessian_f.count = 0

def newton_raphson(f, gradient_f, hessian_f, initial_x, tolerance, max_iterations):
    x = initial_x
    history = [x]
    for i in range(max_iterations):
        grad = gradient_f(x)
        hess = hessian_f(x)
        step = np.linalg.solve(hess, -grad)
        x += step
        history.append(x)
        if np.linalg.norm(step) < tolerance:
            break
    return x, i+1, np.array(history), gradient_f.count, hessian_f.count, f.count

def gradient_descent(f, gradient_f, initial_x, learning_rate, tolerance, max_iterations):
    x = initial_x
    history = [x]
    for i in range(max_iterations):
        grad = gradient_f(x)
        if np.linalg.norm(grad) < tolerance:
            break
        x -= learning_rate * grad
        history.append(x)
    return x, i+1, np.array(history), gradient_f.count, f.count

def hooke_jeeves(f, initial_x, step_size, tolerance):
    x = initial_x
    history = [x]
    step = step_size
    n = len(initial_x)
    
    while step > tolerance:
        x_best = x.copy()
        f_best = f(x_best)
        
        for i in range(n):
            for sign in [-1, 1]:
                x_new = x.copy()
                x_new[i] += sign * step
                f_new = f(x_new)
                
                if f_new < f_best:
                    x_best = x_new
                    f_best = f_new
        
        if f_best < f(x):
            x = x_best
        else:
            step /= 2
        
        history.append(x)
    
    return x, len(history), np.array(history), f.count

def random_search_with_backtracking(f, initial_x, step_size, max_iterations, tolerance):
    x = initial_x
    history = [x]
    best_x = x
    best_f = f(x)
    
    for _ in range(max_iterations):
        step = step_size * np.random.randn(*x.shape)
        x_new = x + step
        f_new = f(x_new)
        
        if f_new < best_f:
            best_x = x_new
            best_f = f_new
            x = x_new
        else:
            x = best_x + step_size * np.random.randn(*x.shape)
        
        if np.linalg.norm(step) < tolerance:
            break
        
        history.append(x)
    
    return best_x, len(history), np.array(history), f.count

# Установка параметров
initial_x = np.array([-1.0, 1.0])  # начальное приближение
tolerance = 1e-5  # порог сходимости
max_iterations = 100000  # максимальное количество итераций

# Применение метода Ньютона-Рафсона
result_newton, iterations_newton, _, grad_count_newton, hess_count_newton, f_count_newton = newton_raphson(f, gradient_f, hessian_f, initial_x, tolerance, max_iterations)

# Применение метода градиентного спуска
learning_rate = 0.0019
result_gradient, iterations_gradient, _, grad_count_gradient, f_count_gradient = gradient_descent(f, gradient_f, initial_x, learning_rate, tolerance, max_iterations)

# Применение метода Хука-Дживса
step_size = 0.5
result_hooke, iterations_hooke, _, f_count_hooke = hooke_jeeves(f, initial_x, step_size, tolerance)

# Применение метода случайного поиска с возвратом
step_size = 0.1
result_random, iterations_random, _, f_count_random = random_search_with_backtracking(f, initial_x, step_size, max_iterations, tolerance)

# Вывод результатов
print("Метод Ньютона-Рафсона:")
print("Решение:", result_newton)
print("Значение функции в минимуме:", f(result_newton))
print("Количество итераций:", iterations_newton)
print("Количество вычислений градиента:", grad_count_newton)
print("Количество вычислений гессиана:", hess_count_newton)
print("Количество вычислений функции:", f_count_newton)
print()

print("Метод градиентного спуска:")
print("Решение:", result_gradient)
print("Значение функции в минимуме:", f(result_gradient))
print("Количество итераций:", iterations_gradient)
print("Количество вычислений градиента:", grad_count_gradient)
print("Количество вычислений функции:", f_count_gradient)
print()

print("Метод Хука-Дживса:")
print("Решение:", result_hooke)
print("Значение функции в минимуме:", f(result_hooke))
print("Количество итераций:", iterations_hooke)
print("Количество вычислений функции:", f_count_hooke)
print()

print("Метод случайного поиска с возвратом:")
print("Решение:", result_random)
print("Значение функции в минимуме:", f(result_random))
print("Количество итераций:", iterations_random)
print("Количество вычислений функции:", f_count_random)
