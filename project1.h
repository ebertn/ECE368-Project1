#include <stdio.h>
#include <math.h>


typedef struct _Task
{
	int arrival_time;
	int priority; 
	int service_time;
	struct _Task *next; 
}Task;



 
