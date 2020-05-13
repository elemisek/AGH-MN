import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()

file = "czebyszew.txt"
data = np.loadtxt(file)
file2 = "points.txt"
data2 = np.loadtxt(file2)

x=data[:,0]
Wn=data[:,1]
x2=data2[:,0]
dots=data2[:,1]
n=['n=5', 'n=10', 'n=15', 'n=20']
n2=5
m=0
y=[]
k=501

for i in range(0,2004):
    y.append(1./(1+x[i]*x[i]))

for a in range(0,4):
    plt.subplot(2,2,a+1)
    plt.plot(x[a*k:a*k+k], Wn[a*k:a*k+k], color='#f25c00')

    plt.plot(x[a*k:a*k+k], y[a*k:a*k+k], linewidth=0.7, color='#000000')

    plt.legend([n[a], 'f(x)'])
    plt.plot(x2[m:m+n2+1], dots[m:m+n2+1], linestyle='', color='#104176', marker='.')
    m=m+n2+1
    n2=n2+5
    plt.xlabel('x')
    plt.grid(True)

plt.suptitle('węzły zoptymalizowane')
plt.subplots_adjust(left=0.08, bottom=0.1, right=0.98, top=0.93, wspace=0.2, hspace=0.4)

plt.savefig("chart_b.png")

