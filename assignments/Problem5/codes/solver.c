#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

//Let the differential equation we want to solve is (an)*(yn)+(an-1)*(yn-1)+...+(a0)*(y)+c=0 where yi is ith derivative of y and ai is a constant
//The output of the recorddata function will be all the values of yk = y(x+kh) in an array where k is an integer

double* recorddata(double lowerbound, double upperbound, double stepsize, double initialy0, double initialyprime0){
	int no_datapoints = (int)((upperbound-lowerbound)/stepsize)+1;
	double* y_values = malloc(no_datapoints*sizeof(double));
	double y1 = initialy0;
	double y2 = initialyprime0;
	for(int i=0; i<no_datapoints; i++){
		y_values[i] = y1;
		y1 = (y1*(4+stepsize*stepsize)+4*y2*stepsize)/(4-stepsize*stepsize);
		y2 = (y2*(4+stepsize*stepsize)+4*y1*stepsize)/(4-stepsize*stepsize);
	}
	return y_values;
}

int main(){
    double initialy0 = 1;
    double initialyprime0 = 0;
    double lowerbound = 0.0;
    double upperbound = 10.0;
    //taking the datapoints between 0 and 10
    double stepsize = 0.1;// h = 0.001

    // Record data using the provided recorddata function
    double* results = recorddata(lowerbound, upperbound, stepsize, initialy0, initialyprime0);

    // Print results
    int no_datapoints = (int)((upperbound - lowerbound) / stepsize);
    for (int i = 0; i < no_datapoints; i++) {
    	printf("This is value at x=%lf :: %lf\n",(i+1)*stepsize,results[i]);
    }
    free(results); // Free memory for the result array

    return 0;
}
