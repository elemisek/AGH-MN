import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

file = "wyniki_1_"+sys.argv[1]+".txt"
data = np.loadtxt(file)

x=data[:,0]
y=data[:,2]

plt.plot(x, y, linewidth=1)
plt.title("k=10, sygnał zaszumiony")
plt.xlabel("i")

#plt.show()
plt.savefig("chart_1_"+sys.argv[1]+".png")