import numpy as np
import matplotlib.pyplot as plt

def pmf(x):
    if x == 0:
        return 1/8
    elif x == 1:
        return 3/8
    elif x == 2:
        return 3/8
    elif x == 3:
        return 1/8
    else:
        return 0

x_values = np.array([-1,0,1,2,3,4])
y_values = np.array([pmf(x) for x in x_values])

plt.figure(figsize=(8, 6))
markerline, stemlines, baseline = plt.stem(x_values, y_values)
plt.setp(markerline, 'markerfacecolor', 'red')
plt.setp(stemlines, 'color', 'red')
plt.setp(baseline, 'color', 'gray', 'linewidth', 1)

plt.xlabel('x')
plt.ylabel('$P(X)$')
plt.grid(True)
plt.savefig("../figs/pmf.png")

