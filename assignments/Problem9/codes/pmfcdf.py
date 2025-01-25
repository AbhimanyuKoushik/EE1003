import ctypes
import numpy as np
import matplotlib.pyplot as plt

# Load the shared object file
# Replace 'binomial.so' with the actual compiled .so file name
binomial_lib = ctypes.CDLL('./solver.so')

# Define the function signature
binomial_rv = binomial_lib.binomial_rv
binomial_rv.restype = ctypes.POINTER(ctypes.c_double)  # Function returns a pointer to double
binomial_rv.argtypes = [ctypes.c_double, ctypes.c_int]  # Arguments: double pval, int no_events

def call_binomial_rv(pval, no_events):
    # Call the C function
    result_ptr = binomial_rv(ctypes.c_double(pval), ctypes.c_int(no_events))
    
    # Convert the result into a Python list
    pmf = [result_ptr[i] for i in range(no_events + 1)]
    
    # Free the memory allocated in C (since malloc was used)
    binomial_lib.free(result_ptr)
    
    return pmf

# Parameters
pval = 0.5  # Probability of success
no_events = 3  # Number of trials

# Get the PMF from the C function
pmf = call_binomial_rv(pval, no_events)

# Plot the PMF
x = np.arange(len(pmf))
y = np.array([pmf[i] for i in x])
cdf = np.cumsum(pmf)

plt.figure(figsize=(8, 6))
markerline, stemlines, baseline = plt.stem(x, y)
plt.setp(markerline, 'markerfacecolor', 'red')
plt.setp(stemlines, 'color', 'red')
plt.setp(baseline, 'color', 'gray', 'linewidth', 1)
plt.xlabel('x')
plt.ylabel('$p_X(k)$')
plt.grid(True)
plt.savefig("../figs/pmf.png")
plt.show()


plt.figure(figsize=(8, 6))
markerline, stemlines, baseline = plt.stem(x, cdf)
plt.setp(markerline, 'markerfacecolor', 'red')
plt.setp(stemlines, 'color', 'red')
plt.setp(baseline, 'color', 'gray', 'linewidth', 1)
plt.xlabel('x')
plt.ylabel('$F_{X}(k)$')
plt.grid(True)
plt.savefig("../figs/cdf.png")
plt.show()

