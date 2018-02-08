#include<stdio.h>
#include<math.h>

#include "project1.h"

int main(int argc, char** argv){
	// // Test queue_pop method
    // Task* first = malloc(sizeof(Task));
    // first->priority = 1;
    // Task* second = malloc(sizeof(Task));
    // second->priority = 0;
    // Task* third = malloc(sizeof(Task));
    // third->priority = 1;
    //
    // Task* list = NULL;
    //
    // // enqueue(&list, first);
    // // print_queue(stdout, list);
    // // enqueue(&list, second);
    // // print_queue(stdout, list);
    // // enqueue(&list, third);
    //
    // print_queue(stdout, list);
    //
    // int rand1 = generate_rate(0.5);
    //
    // for(int i = 0; i < 1; i++){
    //     int rand = generate_rate(0.001);
    //
    //     printf("\n%d\n", rand);
    // }
    //
    // free_queue(list);
    //
    //Test reading file and creating queue
    FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		return EXIT_FAILURE;
	}
	Task* head = NULL;
	//read in file and create queue
	read_input(fp, &head);
    //print_queue(stdout, head);
    fclose(fp);

    simulation(&head);

    //free_queue(head);


    //
    // printf("\n=================Generated Queue=======================\n");
    // Task* queue = generate_queue(0.5, 0.7, 1, 20);
    //
    // print_queue(stdout, queue);
    //
    // free_queue(queue);

    return EXIT_SUCCESS;
}
