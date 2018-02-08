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
		enqueue(queue, new_task, &cmp_pre_arrival);//push new task node onto the queue
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
        enqueue(&queue, new_task, &cmp_pre_arrival);
    }

    // Generate 1s
    for(int i = 0; i < num; i++){
        Task *new_task = malloc(sizeof(*new_task));
    	if(new_task == NULL) { return NULL; }
    	new_task->arrival_time = generate_rate(lam1);
        new_task->priority = 1;
        new_task->service_time = generate_rate(mu);
        enqueue(&queue, new_task, &cmp_pre_arrival);
    }

    return queue;
}

void simulation(Task** pre_queue){
    int t = 0;
    Task* post_queue = NULL;
    int service_finished_time = 0;

    while(!is_empty(*pre_queue) || !is_empty(post_queue)){ // There are still tasks
        Task* next = queue_pop(pre_queue);

        do {
            enqueue(&post_queue, next, &cmp_post_arrival);
            next = queue_pop(pre_queue);
            print_queue(stdout, post_queue);
        } while(next->arrival_time <= t);

        printf("Outer\n");

        serve(&post_queue, &service_finished_time, t);

        t++;
    }

    printf("Pre Queue:\n");
    print_queue(stdout, *pre_queue);

    printf("Post Queue:\n");
    print_queue(stdout, post_queue);

    printf("\nFinish t = %d", t);
}

void serve(Task** post_queue, int* service_finished_time, int t){

    if(*service_finished_time = t){ // Server isn't busy
        if(!is_empty(*post_queue)){ // Queue isn't empty

            // When the server will finished serving
            *service_finished_time = t + (*post_queue)->service_time;

            // Pop and free next task
            Task* served_task = queue_pop(post_queue);
            free_queue(served_task);
        }
    }
}
