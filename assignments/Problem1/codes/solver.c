#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Let the differential equation we want to solve is (an)*(yn)+(an-1)*(yn-1)+...+(a0)*(y)+c=0 where yi is ith derivative of y and ai is a constant
//The output of the recorddata function will be all the values of yk = y(x+kh) in an array where k is an integer

double* vectorfunction(int order, double coefficients[order+2]){
	//an = coeff[0], an-1=coeff[1], ... , a1 = coeff[order-1], a0 = coeff[order], c = coeff[order+1]
	double* outputvector = (double*)malloc(order*sizeof(double));
	for(int i=1;i<order+1;i++){
		outputvector[i-1] = -coefficients[i]/coefficients[0];
	}
	return outputvector;
	//outputs an array with elements [(-(an-1)/an),(-(an-2)/an),...,(-a0/an)]
}

double* recorddata(double lowerbound, double upperbound, int order,  double coefficients[order+2], double initialconditions[order], double stepsize){
	double y[order];
	for(int i=0;i<order;i++){
		y[i] = initialconditions[i];
	}
	//The vector_y is [y(t), y'(t), ..., yn-1(t)]
	//It is initialised to the initial conditions which are part of input given by user 
	double* output_a = vectorfunction(order, coefficients);
	//output_a is now the array with elements [(-(an-1)/an),(-(an-2)/an),...,(-a0/an)]
	int no_datapoints = ((upperbound-lowerbound)/stepsize);
	//It is max no of points which we want to plot, The lower bound is min value of x, upper bound is max value of x, stepsize is the value of h
	double* yvalues = malloc(no_datapoints*sizeof(double));
	for(int i = 0; i<no_datapoints; i++){
	//generating the vector_y for each value of t = lowerbound+stepsize*i until t reaches upperbound so all the vector_y values for each t are recorded at some point of time
		for(int j = 0; j <= order -1; j++){
			y[order-1] += stepsize*(output_a[j])*(y[order-1-j]);
		}
		y[order-1] -= stepsize*(coefficients[order+1]/coefficients[0]);
		//(yn-1)(t+h) = (yn-1)(t)+h*((-(an-1)/an)*(yn-1)+(-(an-2)/an)*(yn-2)+...+(-a0/an)*(y)+(-c/an))
		for(int n = order - 2; n>=0; n--){
			y[n] = y[n]+stepsize*y[n+1];
		}
		//rest yi(t+h) = yi(t) + h*(yi+1)(t)
		yvalues[i] = y[0];
		//recorded y(t) in each iteration in yvalues which should be the output
	}
	return yvalues;
}
int main(){
    int order = 2; //The differential which I have to solve is y''+1 = 0
    double coefficients[] = {1.0, 0.0, 0.0, 1.0};
    double initialconditions[] = {0.0, 0.0}; //Took initial conditions as y(0) = 0, y'(0) = 0 
    double lowerbound = 0.0;
    double upperbound = 10.0;
    //taking the datapoints between 0 and 10
    double stepsize = 0.01;// h = 0.01

    // Record data using the provided recorddata function
    double* results = recorddata(lowerbound, upperbound, order, coefficients, initialconditions, stepsize);

    // Print results
    int no_datapoints = (int)((upperbound - lowerbound) / stepsize);
    for (int i = 0; i < no_datapoints; i++) {
    	printf("This is value at x=%lf :: %lf\n",(i+1)*stepsize,results[i]);
    }
    free(results); // Free memory for the result array

    return 0;
}
