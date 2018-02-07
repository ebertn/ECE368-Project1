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
	fprintf(fp, "NULL\n");
}

// Prints a single Task
void print_task(FILE* fp, Task* list){
	if(list == NULL){
		fprintf(fp, "NULL");
	} else {
		fprintf(fp, "%d", list->val); // TODO: Update when we have all the vals in Task struct
	}
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
