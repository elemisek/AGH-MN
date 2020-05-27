import numpy as np
import matplotlib.pyplot as plt
import sys

fig = plt.figure()

file = "wyniki_simp" + sys.argv[1] + ".txt"
data = np.loadtxt(file)

x=[11,21,51,101,201]
ax=plt.subplot()
ax.set_xticks(x)
ax.set_xticklabels(['11','21','51','101','201'])
plt.plot(x, data, marker='.', linewidth='1')
plt.legend(["m = " + sys.argv[2] + ", k = " + sys.argv[3]])
plt.xlabel("$n$")
plt.ylabel("$|C-I|$")
plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
#plt.show()
plt.savefig("chart_simp" + sys.argv[1] + ".png")
