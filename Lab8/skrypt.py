import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "Wyniki_cos_20.txt"
file2 = "Wyniki_wezly_cos_20.txt"
data = np.loadtxt(file)
data2 = np.loadtxt(file2)

x=data[:,0]
y=data[:,1]
f=data[:,2]
x2=data2[:,0]
w=data2[:,1]

plt.plot(x,y)

plt.plot(x2,w, linestyle='', color='#104176', marker='.', markersize=12)

plt.plot(x,f, color='black')

plt.xlabel('x')
plt.grid(True)
plt.legend(['n=5', 'f(x)'])

plt.savefig("chart_cos_20.png")
