#include<stdio.h>
#include<math.h>

#include "project1.h"

int main(){
    printf("Started\n");
	// Test queue_pop method
    Task* first = malloc(sizeof(Task));
    first->priority = 1;
    Task* second = malloc(sizeof(Task));
    second->priority = 0;
    Task* third = malloc(sizeof(Task));
    third->priority = 1;

    Task* list = NULL;

    enqueue(&list, first);
    print_queue(stdout, list);
    enqueue(&list, second);
    print_queue(stdout, list);
    enqueue(&list, third);

    //enqueue(&first, first);
    // enqueue(&first, second);
    // enqueue(&first, third);

    // first->next = second;
    // second->next = third;
    // third->next = NULL;

    //print_queue(stdout, *loop);

    //Task* popped = queue_pop(&first);

    print_queue(stdout, list);
    //print_queue(stdout, popped);

    //queue_push(&first, popped);
    //print_queue(stdout, popped);

    int rand1 = generate_rate(0.5);

    for(int i = 0; i < 1; i++){
        int rand = generate_rate(0.001);

        printf("\n%d\n", rand);
    }

    free_queue(list);
    //free_queue(popped);

    return EXIT_SUCCESS;
}
