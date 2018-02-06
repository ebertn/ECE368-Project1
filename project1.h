#include <stdio.h>
#include <math.h>


typedef struct _Task
{
	long int arrival_time;
	int priority; 
	long int service_time;
	void *next; 
}Task;



 
