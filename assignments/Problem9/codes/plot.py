import ctypes
import numpy as np
import matplotlib.pyplot as plt
gen = ctypes.CDLL('./solver.so')

gen.run_sim.argtypes = [
        ctypes.c_int, ctypes.POINTER(ctypes.c_double)
]

gen.run_sim.restype = None
max_tosses = 15000
points = np.zeros((max_tosses, 2), dtype=np.double)

gen.run_sim(
    int(max_tosses), 
    points.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
)
fig = plt.figure()
ax = plt.gca()
plt.axhline(y=0.875, color='black', linestyle='--', label='y = 0.875')
plt.scatter(points[0:, 0], points[:, 1],s=1, c='r', linestyle='-', label = "Line plot")
plt.legend(loc = "best")
ax.set_xlabel('X')
ax.set_ylabel('Y')
plt.savefig('../figs/fig.png')
plt.show()

