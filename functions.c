#include <stdio.h> 
#include <math.h>
#include "project1.h"
#include <stdlib.h>

// File for our functions

int  generate_rate(double InputRate) //InputRate is Lambda or Mu
{
	//generates random numbers
	int random_value = rand();
	float unit_rand = random_value / (double)RAND_MAX;
	return ceil((-1/InputRate) * log(1 - unit_rand));
}


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
		fprintf(fp, "%d", list->arrival_time); // TODO: Update when we have all the vals in Task struct
	}
}


void print_queue(FILE* fp, Task* list){
	while (list != NULL) {
		print_task(fp, list);
		fprintf(fp, "->");
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



void read_input(FILE *fp, Task **queue )
{
	fseek(fp, 0L, SEEK_SET);//file starts at the beginning; 

	while(!feof(fp))
	{
		//create TASK node 
		Task *new_task = malloc(sizeof(*new_task));//get memory for new task node	
		fscanf(fp,"%d %d %d ", &(new_task -> arrival_time), &(new_task -> priority), &(new_task -> service_time));//, &(new_task -> priority), &(new_task -> service_time));//scan in data
		enqueue(queue, new_task);//push new task node onto the queue
	}
	
}



/*
void simulation () // figure out inputs
{
	//arrival
	if(server)
	{
		sim_time = arrival_time;
		
		c_in += 1; 
		
*/
	

