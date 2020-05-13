import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

output = "output_part1.txt"
data = np.loadtxt(output)

real=data[:,0]
imag=data[:,1]

n=21

for i in np.arange(0,4):
    plt.plot(real[i*n:i*n+n-1], imag[i*n:i*n+n-1], marker='o')

plt.grid(True)
plt.xlabel('Re(z)')
plt.ylabel('Im(z)')
plt.legend([r'$z^{(0)}$', r'$z^{(1)}$', r'$z^{(2)}$', r'$z^{(3)}$'], loc=2)

plt.savefig("chart1.png")


