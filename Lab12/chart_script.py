import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

file = "wyniki" + sys.argv[1] + ".txt"
data = np.loadtxt(file)

plt.plot(data, marker='.')
plt.legend(["m = " + sys.argv[2] + ", k = " + sys.argv[3]])
plt.xlabel("l")
plt.ylabel("$I$")  

#plt.show()
plt.savefig("chart" + sys.argv[1] + ".png")

#plt.clf()

#file = "wyniki_simp" + sys.argv[1] + ".txt"
#data = np.loadtxt(file)

