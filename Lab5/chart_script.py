import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "results.txt"
data = np.loadtxt(file)

nr_iter = data[7:, 0]
lambd = data[7:, 2:]
colors = ['blue', 'maroon', 'red', 'green', 'gray', 'orange']

for i in np.arange(0,6):
        plt.plot(nr_iter, lambd[:, i], colors[i], linewidth='2', marker='.', markersize='8')

plt.axis([0,11,0,0.6])
plt.rc('text', usetex=True)
plt.legend([r'$\lambda_1$', r'$\lambda_2$', r'$\lambda_3$', r'$\lambda_4$', r'$\lambda_5$', r'$\lambda_6$'], loc=2)
plt.xlabel('numer iteracji')
plt.ylabel(r'$\lambda$')
plt.rc('text', usetex=False)
plt.grid(True)

plt.savefig("chart.png")

