import numpy as np

# Определяем функцию f(x1, x2)
def f(x):
    x1, x2 = x
    return 254 * x1 ** 2 + 506 * x1 * x2 + 254 * x2 ** 2 + 50 * x1 + 130 * x2 - 111

# Определяем градиент функции f(x1, x2)
def grad_f(x):
    x1, x2 = x
    df_dx1 = 508 * x1 + 506 * x2 + 50
    df_dx2 = 506 * x1 + 508 * x2 + 130
    return np.array([df_dx1, df_dx2])

def gradient_descent(f, grad_f, x0, learning_rate=0.01, max_iterations=1000, tol=1e-6):
    x = x0
    for i in range(max_iterations):
        grad = grad_f(x)
        x_new = x - learning_rate * grad
        if np.linalg.norm(x_new - x) < tol:
            break
        x = x_new
    return x, f(x)

# Начальное приближение
x0 = np.array([0, 0])

# Запуск метода градиентного спуска
result_gradient_descent = gradient_descent(f, grad_f, x0)
print("Минимум найден в точке (метод градиентного спуска):", result_gradient_descent[0])
print("Значение функции в минимуме (метод градиентного спуска):", result_gradient_descent[1])