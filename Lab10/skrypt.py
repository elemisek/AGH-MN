import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "result1.txt"
data = np.loadtxt(file)

x=data[:,0]
y=data[:,1:5]

for n in np.arange(0,4):
	plt.plot(x, y[:,n], marker=".")

plt.xlabel('Iteracja')
plt.title(r'$x_1=-0.5, f_1(x)$')
plt.legend([r'$x_1$', r'$x_2$', r'$x_3$', r'$x_m$'])
#plt.legend([r'$F[x_1,x_2]$', r'$F[x_1,x_2,x_3]$'])


plt.savefig("wykres1.png")