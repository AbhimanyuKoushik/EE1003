import ctypes
import numpy as np

# Load the compiled C shared library
lib = ctypes.CDLL('./solver.so')

# Define the argument and return types for the `random` function
lib.random.restype = ctypes.c_double
lib.random.argtypes = [ctypes.c_double, ctypes.c_double]

# Define the argument and return types for the `newton_raphson` function
lib.newton_raphson.restype = ctypes.c_double  # Returning a complex number as double representation
lib.newton_raphson.argtypes = [
    ctypes.c_double, ctypes.c_double,  # Real and imaginary parts of coefficient `a`
    ctypes.c_double, ctypes.c_double,  # Real and imaginary parts of coefficient `b`
    ctypes.c_double, ctypes.c_double   # Real and imaginary parts of coefficient `c`
]

# Define coefficients of the quadratic equation
a_real, a_imag = 2.0, 0.0
b_real, b_imag = -13.0, 0.0
c_real, c_imag = 9.0, 0.0

# Call the `newton_raphson` function to find one root of the quadratic equation
root_real_imag = lib.newton_raphson(
    a_real, a_imag,
    b_real, b_imag,
    c_real, c_imag
)

# Extract the root as a complex number
root_real = ctypes.c_double.from_address(ctypes.addressof(ctypes.c_double(root_real_imag))).value
root_imag = ctypes.c_double.from_address(ctypes.addressof(ctypes.c_double(root_real_imag)) + ctypes.sizeof(ctypes.c_double)).value
root = complex(root_real, root_imag)

# Print the root of the quadratic equation
print("Root of the quadratic equation using Newton-Raphson:")
print(f"Root: {root.real:.4f} + {root.imag:.4f}j")

