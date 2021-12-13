import math
import numpy as np
import matplotlib.pyplot as plt


def Val(x):
    return math.exp(x[0] + 3 * x[1] - 0.1) + math.exp(x[0] - 3 * x[1] - 0.1) + math.exp(-x[0] - 0.1)

def dx_x1(x):
    return math.exp(x[0] + 3 * x[1] - 0.1) + math.exp(x[0] - 3 * x[1] - 0.1) - math.exp(-x[0] - 0.1)

def dx_x2(x):
    return 3 * math.exp(x[0] + 3 * x[1] - 0.1) - 3 * math.exp(x[0] - 3 * x[1] - 0.1) + math.exp(-x[0] - 0.1)

def Square(x):
    return math.sqrt(x[0] * x[0] + x[1] * x[1])

def solve(alpha, beta):
    x = [0, 0]
    t = 1
    Jacobian = [dx_x1(x), dx_x2(x)]
    Direction = [-dx_x1(x) / Square([dx_x1(x), dx_x2(x)]), -dx_x2(x) / Square([dx_x1(x), dx_x2(x)])]
    result = []
    while Val(x) > Val(x) + alpha * t * (Jacobian[0] * Direction[0] + Jacobian[1] * Direction[1]):
        result.append(Val(x))
        t = beta * t
        x[0] = x[0] - t * Jacobian[0]
        x[1] = x[1] - t * Jacobian[1]
        Jacobian = [dx_x1(x), dx_x2(x)]
        Direction = [-dx_x1(x) / Square([dx_x1(x), dx_x2(x)]), -dx_x2(x) / Square([dx_x1(x), dx_x2(x)])]

    return result

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
plt.title("误差随迭代次数改变")
plt.tick_params(labelsize=10)

alpha, beta = 0.01, 0.5
result = solve(alpha, beta)
plt.plot(result, 'g', label=r'alpha=0.01, beta=0.5', lw=2)

alpha, beta = 0.2, 0.5
result = solve(alpha, beta)
plt.plot(result, 'r', label=r'alpha=0.2, beta=0.5', lw=2)

alpha, beta = 0.01, 0.4
result = solve(alpha, beta)
plt.plot(result, 'b', label=r'alpha=0.01, beta=0.4', lw=2)

plt.legend(loc=1)
plt.show()
