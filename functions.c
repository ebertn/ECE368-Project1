#include <stdio.h>
#include <math.h>

#include "project1.h"

int generate_rate(double inputRate)// inputRate is either lambda or Mu
{
  // Randomly Generates an exponential service rate based on the formula
  int random_value = rand();
  float unit_rand = random_value / (double) RAND_MAX;
  return ceil((-1/ inputRate) * log(1-unit_rand));         //This is similar to slide 10 in Week 3 notes
}

void read_input(FILE *fp, Task **queue){
	fseek(fp, 0L, SEEK_SET);//file starts at the beginning;

	while(!feof(fp)){
		Task *new_task = malloc(sizeof(*new_task));//get memory for new task node
		fscanf(fp,"%d %d %d ", &(new_task -> arrival_time), &(new_task -> priority), &(new_task -> service_time));//, &(new_task -> priority), &(new_task -> service_time));//scan in data
		enqueue(queue, new_task);//push new task node onto the queue
	}
}

Task* generate_queue(double lam0, double lam1, double mu, int num){
    Task* queue = NULL;

    // Generate 0s
    for(int i = 0; i < num; i++){
        Task *new_task = malloc(sizeof(*new_task));
    	if(new_task == NULL) { return NULL; }
    	new_task->arrival_time = generate_rate(lam0);
        new_task->priority = 0;
        new_task->service_time = generate_rate(mu);
        enqueue(&queue, new_task);
    }

    // Generate 1s
    for(int i = 0; i < num; i++){
        Task *new_task = malloc(sizeof(*new_task));
    	if(new_task == NULL) { return NULL; }
    	new_task->arrival_time = generate_rate(lam1);
        new_task->priority = 1;
        new_task->service_time = generate_rate(mu);
        enqueue(&queue, new_task);
    }

    return queue;
}
