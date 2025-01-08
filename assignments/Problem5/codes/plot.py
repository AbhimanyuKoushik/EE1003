import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared library
solver = ctypes.CDLL('./solver.so')

# Define the function signature for the C function
solver.recorddata.restype = ctypes.POINTER(ctypes.c_double)
solver.recorddata.argtypes = [
    ctypes.c_double,  # lowerbound
    ctypes.c_double,  # upperbound
    ctypes.c_double,  # stepsize
    ctypes.c_double,  # initialy0
    ctypes.c_double   # initialyprime0
]

# Define parameters
lowerbound = 0.0
upperbound = 10.0
stepsize = 0.001
initialy0 = 1.0
initialyprime0 = 0.0

# Calculate the number of data points
no_datapoints = int((upperbound - lowerbound) / stepsize) + 1

# Call the C function
results_ptr = solver.recorddata(
    ctypes.c_double(lowerbound),
    ctypes.c_double(upperbound),
    ctypes.c_double(stepsize),
    ctypes.c_double(initialy0),
    ctypes.c_double(initialyprime0)
)

# Convert results back to a NumPy array
results = np.ctypeslib.as_array(results_ptr, shape=(no_datapoints,))

# Generate x-values for plotting
x_values = np.linspace(lowerbound, upperbound, no_datapoints)

# Example theoretical y-values for a chosen function
y_function = (1/2)*(np.exp(-x_values)+np.exp(x_values))  # Modify this as needed

# Plot the data
plt.scatter(x_values, results, color='blue', s=10, label='Simulated')
plt.plot(x_values, y_function, color='red', label='Theoretical')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.title("Comparison of Simulated and Theoretical Results")
plt.savefig('../figs/fig.png')  # Save the figure
plt.show()


