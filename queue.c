#include <stdio.h>
#include <math.h>

#include "project1.h"

// Implementation of a FIFO queue of Tasks

// Put a task at the beginning of the queue
Task *queue_push(Task** queue, Task* new_task){
	if(new_task == NULL) {
        return NULL;
    }

	new_task->next = *queue;
	*queue = new_task;

	return new_task;
}

// Removes a Task from the end of the list, in FIFO fashion
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

// Print a queue of Tasks
void print_queue(FILE* fp, Task* list){
	while (list != NULL) {
		// print the memory associated with list->ptr
		print_task(fp, list);
		// print an arrow
		fprintf(fp, "->");
		list = list->next;
	}
	// print NULL and a newline after that
	fprintf(fp, "NULL\n\n");
}

// Prints a single Task
void print_task(FILE* fp, Task* list){
	if(list == NULL){
		fprintf(fp, "NULL");
	} else {
		fprintf(fp, "(%d,%d,%d)", list->arrival_time, list->priority, list->service_time);
	}
}

// Inserts a task into a priority queue at the correct location
Task* enqueue(Task** pq, Task* new_object, int (*cmp_fn)(Task*, Task*)){
	if(new_object == NULL){ return NULL; }

	//print_queue(stdout, *pq);

	if(*pq == NULL || (*cmp_fn)(new_object, *pq) <= 0){//compare_tasks(new_object, *pq) <= 0){
		new_object->next = *pq;
		*pq = new_object;
	} else {
		Task* cur = *pq;
		while(cur->next != NULL && (*cmp_fn)(new_object, cur->next) > 0){//compare_tasks(new_object, cur->next) > 0){
			cur = cur->next;
		}
		new_object->next = cur->next;
		cur->next = new_object;
	}
	return new_object;
}

int cmp_post_arrival(Task* one, Task* two){
	if(one->priority < two->priority){
		return 1; // 1 = keep going
	}
	if(one->priority == two->priority
	&& one->arrival_time < two->arrival_time){
		return 1;
	}
	return -1; // -1 = stop
}

int cmp_pre_arrival(Task* one, Task* two){
	if(one->arrival_time < two->arrival_time){
		return 1; // 1 = keep going
	}
	if(one->arrival_time == two->arrival_time
	&& one->priority < two->priority){
		// return 1;
	}
	return -1; // -1 = stop
}

int is_empty(Task* list){
	return list == NULL;
}

// Frees a linked list
void free_queue(Task *queue){
	Task* temp;
	while(queue != NULL){
		temp = queue;
		queue = queue->next;
		free(temp);
	}
	return;
}
