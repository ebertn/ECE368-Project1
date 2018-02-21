#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define NUM_SERVERS 64

typedef struct _Task {
	int arrival_time;
	int priority;
	int service_time;
	int subtasks[32];
	int num_subtasks;

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
void serve(Task*, int*, int, int, int*, int*, int*, int*);
void simulation(Task**);
int average_qlen(Task**);
void mode_2(char**);
void mode_1(char**);
int num_avaliable_servers(int, int*);
int generate_subtasks(double, int*);
