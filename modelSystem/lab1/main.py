from matplotlib import pyplot as plt
import math
import numpy as np

def inInterval(nums, least, great):
    return sum(1 for elem in nums if (least <= elem < great))

def writeToFile(nums, file_name):
    with open(file_name, 'w') as file:
        for n in nums:
            file.write(str(n) + ' ')

def readFromFile(file_name):
    with open(file_name, 'r') as file:
        nums = file.readline().split(' ')
        nums.remove('')
        nums = list(map(float, nums))
        return nums

def methodVichetov(x0, a=16807, module=2_147_483_647, size=1000):
    nums = [x0 / module]

    for _ in range(size):
        x = a * x0 % module
        y = x / module

        if y in nums:
            return nums

        nums.append(y)
        x0 = x

    return nums

def createPlots(nums):
    plt.hist(nums, bins=11, density=True, color='b', label='Гистограмма')

    sortedNumbers = sorted(nums)
    plt.plot(sortedNumbers, [i / len(sortedNumbers) for i in range(len(sortedNumbers))], color='r', label='Функция распределения')

    plt.xlabel('Значение случайной величины')
    plt.ylabel('Плотность вероятности')
    plt.legend()
    plt.show()

def series(nums):

    numsSort = list(sorted(nums))
    sizeArray = len(nums)

    if sizeArray % 2 == 1:
        medIdx = int((sizeArray + 1) / 2)
        med = numsSort[medIdx]

    else:
        medIdxF = math.floor(sizeArray / 2)
        medIdxC = math.ceil(sizeArray / 2)

        med = numsSort[medIdxF] + numsSort[medIdxC]

    sign = [elem > med for elem in nums] 

    nps, nms = 0, 0

    for counter in range(1, len(sign)):
        if sign[counter] != sign[counter - 1]:
            if sign[counter - 1]:
                nms += 1
            else:
                nps += 1

    r = nms + nps
    nm = sum(1 for s in sign if not s)
    np = sum(1 for s in sign if s)

    mu = 2 * np*nm / sizeArray + 1
    sigma_sq = 2*np*nm*(2*np*nm - sizeArray) / ((sizeArray**2)*(sizeArray - 1))
    sigma = sigma_sq**0.5

    return (r - mu) / sigma

def chi_square(nums):
    size = len(nums)
    m = int(size / 10)
    h = 1 / m
    x = [h*i for i in range(m + 1)]
    n = [inInterval(nums, x[i], x[i+1]) for i in range(m)]
    
    return m / size * sum(map(lambda elem: elem**2, n)) - size

if __name__== '__main__':
    # nums = methodVichetov(2023)
    # writeToFile(nums, 'data.txt')

    nums = readFromFile('data.txt')
    createPlots(nums)

    # Уровень значимости
    print(f'\nseries method:   {series(nums)}\n') 

    print('chi-squared value:', chi_square(nums))

