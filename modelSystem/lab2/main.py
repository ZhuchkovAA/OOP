import numpy as np
from matplotlib import pyplot as plt

def read_from_file(file_name):
    with open(file_name, 'r') as file:
        nums = file.readline().split(' ')
        nums.remove('')
        nums = list(map(float, nums))
        return nums

def create_graph(nums):
    plt.hist(nums, bins=11, density=True, color='b', label='Гистограмма')

    plt.xlabel('Значение')
    plt.ylabel('Плотность')
    plt.legend()
    plt.show()

    sortedNumbers = sorted(nums)
    plt.plot(sortedNumbers, [i / len(sortedNumbers) for i in range(len(sortedNumbers))], color='r', label='Функция распределения')
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

    print('\n\nОбщее: ', r)
    print('Нижняя граница: ', (mu - 1.959963985 * sigma), 'Верхняя граница: ',  (mu + 1.959963985 * sigma))

def inInterval(nums, least, great):
    return sum(1 for elem in nums if (least <= elem < great))

def chi_square(nums):
    size = len(nums)
    m = int(size / 10)
    h = 1 / m
    x = [h*i for i in range(m + 1)]
    n = [inInterval(nums, x[i], x[i+1]) for i in range(m)]
    
    print('\n\nХИ-квадрат: ', m / size * sum(map(lambda elem: elem**2, n)) - size)

def exp_raspr(numbers):
    x0 = 18
    lymbda = 5
    
    new_array = []

    for count in numbers:
        x = x0 - (1 / lymbda) * np.log(1 - count)
        new_array.append(x)

    create_graph(new_array)

    series(new_array)
    chi_square(nums)

    return new_array

def norm_raspr(nums):
    numbers = nums.copy()

    result = []

    while len(numbers) > 12:
        m = 0
        for i in range (-12, 0):
            m += numbers[i]
        result.append(m - 6)
        for i in range (-12, 0):
            numbers.pop(i)

    create_graph(result)

    return result

def norm_raspr_m_s(nums):
    print(nums)
    m = 57
    s = 11**2
    result = np.array(nums)*s + m

    create_graph(result)

def chi_square_V(nums):
    v = 44
    chi = []

    for count in nums:
        chi.append((count + np.sqrt(2*v + 1)) / 2)

    create_graph(chi)

def logist_raspr(nums):
    m = 57
    lymbda = 5

    data = []

    for count in nums:
        data.append(m - lymbda * np.log((1 - count) / count))
    
    create_graph(data)

def disc_SV(nums):
    p = [ 0.27, 0.36, 0.25, 0.12 ]
    x = [1, 2, 3, 4]

    data = []

    for count in nums:

        if count < p[0]:
            data.append(x[0])

        elif count < p[0]+p[1]:
            data.append(x[1])

        elif count < p[0]+p[1]+p[2]:
            data.append(x[2])
        
        else:
            data.append(x[3])

    create_graph(data)

def puasson(nums):
    lymbda = 5
    size = 1000
    i = 0
    k = 1 
    puass = []

    while(i + k < size):
        k = 1
        p = 1
        while(p > np.exp(-lymbda) and i+k < size):
            p = np.prod(nums[i:i+k])
            k += 1
        else:
            puass.append(k)
            i += k

    create_graph(puass)

if __name__ == '__main__':
    nums = read_from_file('data.txt')
    nums_exp = exp_raspr(nums)
    # nums_norm = norm_raspr(nums)
    # norm_raspr_m_s(nums_norm)
    # chi_square_V(nums_norm)
    # logist_raspr(nums)
    # disc_SV(nums)
    # puasson(nums)