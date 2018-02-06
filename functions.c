#include <stdio.h> 
#include <math.h>
// File for our functions

double generate_rate(double InputRate) //InputRate is Lambda or Mu
{
	//generates random numbers
	double random_value = rand();
	double unit_rand = random_value / (double)RAND_MAX;
	return((-1/InputRate) * log(1 - unit_rand));
}


void read_input(int argc, char* argv[], int *service_time, int*arrival_time, int* priority)
{
	if(argc == 4) 
	{
		//MODE 1

	}
	if(argc == 2)
	{
		//MODE 2
	}

