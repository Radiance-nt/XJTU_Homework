import numpy as np
from matplotlib import pyplot as plt

pH = float(input('pH= '))
pE = float(input('pE= '))
LN = float(input('LN= '))
LS = float(input('LS= '))

y2 = LS * pH / ((LS - 1) * pH + 1)
y1 = pH
y0 = LN * pH / ((LN - 1) * pH + 1)


def func(x):
    y = 0
    if x == 1:
        y = LS * pH / ((LS - 1) * pH + 1)
    elif x == 0:
        y = LN * pH / ((LN - 1) * pH + 1)
    elif x == pE:
        y = pH
    elif 0 < x < pE:
        y = y0 + x * (y1 - y0) / pE
    else:
        y = y1 + (x - pE) * (y2 - y1) / (1 - pE)
    return y


vfunc = np.vectorize(func)

x = np.linspace(0, 1, 200)
res = vfunc(x)

plt.plot(x, res, 'gray', linestyle='-', color='r', marker='')
plt.savefig("test.png")

plt.show()
