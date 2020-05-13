import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt"
data = np.loadtxt(file)

nr_iter = data[7:, 0]
lambd = data[7:, 2]

plt.plot(nr_iter, lambd, color='red', linewidth='2', marker='.', markersize='8')

plt.axis([0,11,0,0.3])
plt.rc('text', usetex=True)
plt.legend([r'$\lambda_1$'], loc=4)
plt.xlabel('numer iteracji')
plt.ylabel(r'$\lambda$')
plt.rc('text', usetex=False)
plt.grid(True)

plt.savefig("chart2.png")

