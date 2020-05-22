import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

file = "wyniki_2_"+sys.argv[1]+".txt"
data = np.loadtxt(file)

x=data[:,0]
y=data[:,1]

plt.plot(x, y, linewidth=1)
plt.axis([0,100,-100,600])
plt.title("k=10, transformata Fouriera")
plt.xlabel("$\omega$")

#plt.show()
plt.savefig("chart_2_2_"+sys.argv[1]+".png")