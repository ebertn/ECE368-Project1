#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Task {
    int val;
    struct _Task *next;
} Task;

Task* queue_push(Task**, Task*);
Task* queue_pop(Task**);
void free_queue(Task *queue);
void print_queue(FILE*, Task*);
void print_task(FILE*, Task*);
