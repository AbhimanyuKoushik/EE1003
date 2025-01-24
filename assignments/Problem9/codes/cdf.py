import numpy as np
import matplotlib.pyplot as plt

def cdf(x):
    if x < 0:
        return 0
    elif 0 <= x < 1:
        return 1/8
    elif 1 <= x < 2:
        return 1/2
    elif 2 <= x < 3:
        return 7/8
    else:
        return 1
x_values = np.array([-1,0,1,2,3,4,5])
y_values = np.array([cdf(np.floor(x)) for x in x_values])
plt.figure(figsize=(8, 6))
markerline, stemlines, baseline = plt.stem(x_values, y_values)
plt.setp(markerline, 'markerfacecolor', 'red')
plt.setp(stemlines, 'color', 'red')
plt.setp(baseline, 'color', 'gray', 'linewidth', 1)

plt.xlabel('x')
plt.ylabel('$F_X(X)$')
plt.grid(True)
plt.savefig("../figs/cdf.png")
