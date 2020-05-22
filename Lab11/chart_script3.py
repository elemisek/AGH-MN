import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

file = "wyniki_3_"+sys.argv[1]+".txt"
data = np.loadtxt(file)

x=data[:,0]
y=data

plt.plot(x,y[:,1], color="red")
plt.plot(x,y[:,2], color="black")
plt.title("k="+sys.argv[1])
plt.xlabel("i")
plt.legend(["sygnał niezaszumiony","sygnał odszumiony"])

#plt.show()
plt.savefig("chart_3_"+sys.argv[1]+".png")