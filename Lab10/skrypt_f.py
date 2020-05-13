import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "function.txt"
data = np.loadtxt(file)

x=data

plt.plot(x[:,0], x[:,1])

plt.xlabel('x')

plt.title(r'$f_1(x), [-1.5,1]$')

plt.savefig("function.png")