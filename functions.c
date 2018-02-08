#include <stdio.h> 
#include <math.h>
#include "project1.h"
#include <stdlib.h>

// File for our functions

Task *queue_push(Task** queue, Task* new_task)
{
        if(new_task == NULL)
        {
                return NULL;
        }

        new_task->next = *queue;
        *queue = new_task;

        return new_task;
}


void print_task(FILE* fp, Task* list){
	if(list == NULL){
		fprintf(fp, "NULL");
	} else {
		fprintf(fp, "(%d, %d)", list->arrival_time, list -> priority); // TODO: Update when we have all the vals in Task struct
	}
}


void print_queue(FILE* fp, Task* list){
	while (list != NULL) {
		print_task(fp, list);
		fprintf(fp, "->" );
		list = list->next;
	}
	fprintf(fp, "NULL\n");
}

void free_queue(Task *queue){
	Task* temp;
	while(queue != NULL){
		temp = queue;
		queue = queue->next;
		free(temp);
	}
	return;
}
int compare_tasks(Task* one, Task* two){
	if(one->priority <= two->priority){
		return 1;
	}
	return -1;
}
//place queue nodes in correct positions 	
Task* enqueue(Task** pq, Task* new_object){
	if(new_object == NULL){ return NULL; }
	if(*pq == NULL || compare_tasks(new_object, *pq) <= 0){
		new_object->next = *pq;
		*pq = new_object;
	} else {
		Task* cur = *pq;
		while(cur->next != NULL && compare_tasks(new_object, cur->next) > 0){
			cur = cur->next;
		}
		new_object->next = cur->next;
		cur->next = new_object;
	}
	return new_object;
}

int generate_rate(double inputRate)// inputRate is either lambda or Mu
{
  // Randomly Generates an exponential service rate based on the formula
  int random_value = rand();
  float unit_rand = random_value / (double) RAND_MAX;
  return ceil((-1/ inputRate) * log(1-unit_rand));         //This is similar to slide 10 in Week 3 notes
}

//mode 2 input file function 
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

void mode_2(char *argv[]) {	
                
	FILE* fp = fopen(argv[1], "r"); //input file open for reading 
       	Task* head = NULL;//queue header
    	read_input(fp, &head);
       	print_queue(stdout, head);
       	fclose(fp);
        free_queue(head);
}  	

void mode_1(char *argv[]){
	double lam0 = atof(argv[1]); //first arrival time
	double lam1 = atof(argv[2]);//arrivl time 
	double mu = atof(argv[3]); //service time
	int num_tasks = atoi(argv[4]);//number of tasks to be performed for both 1's and 0's
	Task *queue = generate_queue(lam0,lam1,mu, num_tasks); //generates both queues
	print_queue(stdout, queue);
	free_queue(queue);
}
	
Task* queue_pop(Task **queue){
	if(*queue == NULL){
		return NULL;
	}

	Task* prev;
	Task* cur = *queue;
	while(cur->next != NULL){
		prev = cur;
		cur = cur->next;
	}
	prev->next = NULL;
	return cur;

}


void print_output(double wait1, double wait0, double ave_qlen, double ave_cpu){
	printf("\naverage_wait_0 = %lf\n",wait0);
	printf("average_wait_1 = %lf\n", wait1);
	printf("average_queue_length = %lf\n", ave_qlen);
	printf("average_CPU_utilization = %lf\n", ave_cpu);
}



//running average of qlen ("queue length)
void average_qlen(int *qlen_sum, Task** post_queue){

	if(*queue == NULL)//queue is empty add zero to the queue
	{
		qlen_sum += 0;
	}
	else
	Task * cur = *queue;
	while(cur->next != NULL)//find the length of the current queue and add that to the current running total
	{
		qlen_sum += 1;
		cur = cur->next;
	}
	
} 


	
