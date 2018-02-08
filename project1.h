#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct _Task {
	int arrival_time;
	int priority;
	int service_time;
	struct _Task *next;
} Task;

// Queue.c
Task* queue_push(Task**, Task*);
Task* queue_pop(Task**);
void free_queue(Task *queue);
void print_queue(FILE*, Task*);
void print_task(FILE*, Task*);
Task* enqueue(Task**, Task*, int (*cmp_fn)(Task*, Task*));
int cmp_pre_arrival(Task*, Task*);
int cmp_post_arrival(Task*, Task*);
int is_empty(Task*);
Task* get_head(Task**);

// Functions.c
int generate_rate(double);
void read_input(FILE *fp, Task **queue);
Task* generate_queue(double, double, double, int);
void serve(Task**, int*, int, int*, int*, int*, int*);
void simulation(Task**);
