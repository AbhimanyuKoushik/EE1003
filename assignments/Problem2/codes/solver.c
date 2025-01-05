#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute the derivatives
void compute_derivatives(double x, double* y, double* dydx, double* derivatives) {
    double dydx1 = y[1];
    double dydx2 = -sqrt(fmax(0, -cos(y[1]))); // Ensure sqrt has a non-negative argument

    derivatives[0] = dydx1;
    derivatives[1] = dydx2;
}

// Euler method to solve the DE
void solve_de(double lowerbound, double upperbound, double stepsize, double* initialconditions, double** results, int* num_points) {
    int order = 2;
    int max_points = (int)((upperbound - lowerbound) / stepsize) + 1;
    *num_points = max_points;

    *results = (double*)malloc(max_points * sizeof(double));
    double y[2] = {initialconditions[0], initialconditions[1]};
    double derivatives[2];

    double x = lowerbound;
    for (int i = 0; i < max_points; i++) {
        (*results)[i] = y[0]; // Store y
        compute_derivatives(x, y, derivatives, derivatives);

        // Update y and dy/dx using Euler method
        y[0] += stepsize * derivatives[0];
        y[1] += stepsize * derivatives[1];

        x += stepsize;
    }
}

int main() {
    double lowerbound = 0.0;
    double upperbound = 10.0;
    double stepsize = 0.01;
    double initialconditions[] = {1.0, 0.0}; // y(0) = 0, y'(0) = 0

    double* results;
    int num_points;

    solve_de(lowerbound, upperbound, stepsize, initialconditions, &results, &num_points);

    for (int i = 0; i < num_points; i++) {
        printf("x = %.2f, y = %.6f\n", lowerbound + i * stepsize, results[i]);
    }

    free(results);
    return 0;
}

