#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <math.h>
//The Serial Program

#define n 8*2
#define d 3
#define e 8*1000

double get_rand(double min, double max){
	double x = rand() / (double) RAND_MAX;
	return x * (max - min) + min;
}

double distance2(double p0[d], double p1[d]){
	double x = 0;
	for(int i=0; i<d; ++i){
		double diff = p0[i] - p1[i];
		x += diff * diff;
	}
	return x;//(x is: (p1 - p2)^2)
}

int main(int argc, char* argv[]){
	std::cout << "In The Main Method" << std::endl;
	std::cout << "The Value of n: " << n << std::endl;
	std::cout << "The Value of d: " << d << std::endl;
	//printf("In The Main Method");
	srand(time(0));
	double radius[n];
	double C[n][d];
	//Generate data of points
	for(int i=0; i<n; ++i){
		radius[i] = get_rand(1,5);
		for(int j=0; j<d; ++j){
			C[i][j] = get_rand(-20, 20);
		}
	}
	
	std::cout << "After Finishing For-Loop of initialization of radius and C" << std::endl;
	
	//Compute bounding box.
	double bb[d][2];
	for(int i=0; i<d; ++i){
		bb[i][0] = std::numeric_limits<double>::infinity();
		bb[i][1] = -std::numeric_limits<double>::infinity();
	}
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<d; ++j){
			bb[j][0] = fmin(bb[j][0], C[i][j] - radius[i]);
			bb[j][1] = fmax(bb[j][1], C[i][j] + radius[i]);
		}
	}
	
	//compute the volumw of the bounding box
	double volBB = 1;
	for(int i=0; i<d; ++i){
		volBB *= bb[i][1] - bb[i][0];
	}
	
	//draw samples and perform rejection sampling
	int ePrime = 0;
	for(int i=0; i<e; ++i){
		double pos[d];
		for(int j=0; j<d; ++j){
			pos[j]=get_rand(bb[j][0], bb[j][1]);
		}
		for(int j=0; j<n; ++j){
			if(distance2(pos, C[j]) < radius[j] * radius[j]){
				++ePrime;
			}
		}
	}
	printf("The Number of ePrime is: %d\n", ePrime);
	//compute the volume
	double vol = volBB * (double) ePrime/double(e);
	printf("The Volume is: %3.12f\n", vol);
	printf("The Ending of Main Method\n");
}
