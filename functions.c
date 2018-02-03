#include <stdio.h>
#include <math.h>
// File for our functions

// Put a task at the beginning of the queue
Task *queue_push(Task** queue, Task* new_task){
	if(new_task == NULL) {
        return NULL;
    }

	new_task->next = *queue;
	*queue = new_task;

	return new_task;
}

// Removes the first task on the queue
Task *queue_pop(Task **queue){
	if(*queue == NULL) { return NULL };
	Task* head = *queue;
	*queue = (*queue)->next;
	head->next = NULL;
	return head;
}

// Frees a linked list
void free_queue(Task *queue, void (*destroy_fn)(void *)){
	Task* temp;
	while(queue != NULL){
		temp = queue;
		queue = queue->next;        
		free(temp);
	}
	return;
}
