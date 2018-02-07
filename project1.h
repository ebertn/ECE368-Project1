<<<<<<< HEAD
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
 
// Queue.c
Task* queue_push(Task**, Task*);
Task* queue_pop(Task**);
void free_queue(Task *queue);
void print_queue(FILE*, Task*);
void print_task(FILE*, Task*);

// Functions.c
int generate_rate(double);
