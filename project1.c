#include<stdio.h>
#include<math.h>
#include "project1.h"

int main(int argc, char *argv[]){
	
	(if argc != 2 || argc != 4)
	{
		return EXIT_FAILURE;
	}

	// Test queue_pop method
    Task* first = malloc(sizeof(Task));
    first->val = 1;
    Task* second = malloc(sizeof(Task));
    second->val = 2;
    Task* third = malloc(sizeof(Task));
    third->val = 3;

    first->next = second;
    second->next = third;
    third->next = NULL;

    Task* popped = queue_pop(&first);

    print_queue(stdout, first);
    print_queue(stdout, popped);

    queue_push(&first, popped);
    print_queue(stdout, popped);

    int rand1 = generate_rate(0.5);
    int rand = generate_rate(0.5);
    
    printf("%f ", rand);

    free_queue(first);
    free_queue(popped);
}
