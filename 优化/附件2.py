import numpy as np
from numpy import *
from matplotlib import pyplot as plt

a = 0

while a != 30:
    A = mat(random.randint(1, 5, size=(30, 100)))
    a = np.linalg.matrix_rank(A)
AT = np.transpose(A)
x0 = []
for i in range(0, 100):
    x0.append(0.001 + 1 / 100 * i)
x0 = np.array(x0)
x0 = x0.reshape((100, 1))
b = np.array(A.dot(x0))

beta = 0.8
alpha = 0.0005


def Val(x):
    value = 0
    for i in range(0, 100):
        value += x[i, 0] * log(x[i, 0])
    return value


def Grid(x):
    grid = []
    for i in range(100):
        grid.append(1 + log10(x[i, 0]))
    grid = np.transpose(np.array(grid))
    grid = grid.reshape((100, 1))
    return grid


def Hess(x):
    hess = np.zeros((100, 100))
    for i in range(100):
        hess[i][i] = 1 / x[i, 0]
    return hess


def Direction(x):
    AT = np.transpose(A)
    hess = Hess(x)
    S = np.vstack((np.hstack((hess, AT)), np.hstack((A, np.zeros((30, 30))))))
    grid = Grid(x)
    R = -np.vstack((grid, np.zeros((30, 1))))
    result = ((np.linalg.inv(S)).dot(R))
    direction = result[:100, :]
    return direction


def Lambda(x):
    deri = np.transpose(Grid(x))
    lamb = deri.dot(Direction(x))
    return -lamb[0, 0]


def solve_1(epsilon):
    temp_x1 = x0
    error1 = []
    while 0.5 * (Lambda(temp_x1)) > epsilon:
        error1.append(Lambda(temp_x1))
        t = 1
        direction = Direction(temp_x1)
        O = np.transpose(Grid(temp_x1))
        while Val(temp_x1 + t * direction) > (Val(temp_x1)) - alpha * t * (Lambda(temp_x1)):
            t = beta * t
        temp_x1 = temp_x1 + t * direction
        print(Val(temp_x1))
    return error1


def Dierection2(x, v):
    hess = Hess(x)
    S = np.vstack((np.hstack((hess, AT)), np.hstack((A, np.zeros((30, 30))))))
    R1 = Grid(x) + AT.dot(v)
    R2 = A.dot(x) - b
    R = -np.vstack((R1, R2))
    result = ((np.linalg.inv(S)).dot(R))
    return result


def Norm_2(x, v):
    r1 = Grid(x) + AT.dot(v)
    r2 = A.dot(x) - b
    r = np.vstack((r1, r2))
    r_norm = np.linalg.norm(r)
    return r_norm


def solve_2(epsilon):
    temp_x2 = np.ones((100, 1))
    temp_v2 = np.zeros((30, 1))
    error2 = []
    while Norm_2(temp_x2, temp_v2) > epsilon:
        error2.append(Norm_2(temp_x2, temp_v2))
        result = Dierection2(temp_x2, temp_v2)
        dx = result[0:100, :]
        dv = result[100:131, :]
        t = 1
        while Norm_2(temp_x2 + t * dx, temp_v2 + t * dv) > (1 - alpha * t) * Norm_2(temp_x2, temp_v2):
            t = beta * t
        temp_x2 = temp_x2 + t * dx
        temp_v2 = temp_v2 + t * dv
    return error2


def Val_3(u):
    value = 0
    for i in range(0, 30):
        value += u[i, 0] * b[i, 0]
    sum1 = 0
    for i in range(0, 100):
        aT = np.transpose(A[:, i])
        sum1 += exp(-aT.dot(u) - 1)
    value = value + sum1
    return value


def Grid_3(u):
    one = np.ones((100, 1))
    grid2 = b - A.dot(exp(-AT.dot(u) - one))
    return grid2


def Hess_3(u):
    one = np.ones((100, 1))
    Y = array(exp(-AT.dot(u) - one))
    hess = A.dot(np.diag(Y.flatten()))
    hess = hess.dot(AT)
    return hess


def Dx_3(u):
    hess2I = np.linalg.inv(Hess_3(u))
    grid2 = Grid_3(u)
    dx2 = -hess2I.dot(grid2)
    return dx2


def Lambda_3(u):
    grid2 = Grid_3(u)
    grid2T = np.transpose(grid2)
    dx = Dx_3(u)
    lamb = -grid2T.dot(dx)
    return lamb[0, 0]


def solve_3(epsilon):
    error3 = []
    temp_u = np.zeros((30, 1))
    while 0.5 * Lambda_3(temp_u) > epsilon:
        error3.append(Lambda_3(temp_u))
        t = 1
        dx2 = Dx_3(temp_u)
        while Val_3(temp_u + t * dx2) > Val_3(temp_u) - alpha * t * Lambda_3(temp_u):
            t = beta * t
        temp_u = temp_u + t * dx2
    return error3

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
plt.title("牛顿减少量随迭代次数变化")
plt.tick_params(labelsize=10)
error1 = solve_1(0.0001)
error2 = solve_2(0.0001)
error3 = solve_3(0.000000001)
plt.plot(error1, 'r', label=r'标准牛顿方法', lw=2)
plt.plot(error2, 'g', label=r'不可行初始点的牛顿方法', lw=2)
plt.plot(error3, 'b', label=r'对偶方法', lw=2)
plt.ylim(0, 1)
plt.legend(loc=1)
plt.show()
