def serial_test(data):
    """
    Проверяет последовательность данных на случайность с использованием критерия серий.

    :param data: Последовательность данных (список, массив и т. д.).
    :return: True, если данные считаются случайными, и False в противном случае.
    """
    if len(data) < 3:
        raise ValueError("Последовательность данных должна содержать как минимум 3 элемента")

    # Подсчет количества серий
    series_count = 1
    for i in range(1, len(data)):
        if data[i] != data[i - 1]:
            series_count += 1

    # Ожидаемое количество серий для случайных данных
    expected_series = (2 * len(data) - 1) / 3

    # Рассчитываем статистику теста
    chi_squared = ((series_count - expected_series) ** 2) / expected_series

    # Для определения степени свободы используем условие: df = k - 1, где k - количество различных значений в данных
    distinct_values = len(set(data))
    degrees_of_freedom = distinct_values - 1

    # Выбираем уровень значимости (например, 0.05) и проверяем гипотезу
    alpha = 0.05
    critical_value = 2.706  # Критическое значение для alpha=0.05 и df=2

    return chi_squared < critical_value

# Пример использования
data_sequence = [0, 1, 0, 1, 0, 1, 0, 1]  # Пример случайных данных
is_random = serial_test(data_sequence)
print(f"Последовательность данных случайна: {is_random}")