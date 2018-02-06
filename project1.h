#include <stdio.h>
#include <math.h>


typedef struct _Task
{
	double arrival_time;
	int priority; 
	double service_time;
	double sim_time;
	struct _Task *next; 
}Task;



 
