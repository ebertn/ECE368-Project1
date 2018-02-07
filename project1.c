#include <stdio.h>
#include <math.h>
#include "project1.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	
	/*double input_rate = 70;
	double exp_rate = generate_rate(input_rate);
	
	printf("\nGenerate function test\n");
	printf("generated value: %d\n", exp_rate);

	printf("RAND_MAX = %d", RAND_MAX);
	*/
	printf("\n========START=====\n");
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}
	Task *head = NULL;	
	//read in file and create queue
	read_input(fp, &head);
	
	//print queue
	
	
	print_queue(stdout, head);
	

	//memory management
	free_queue(head);
	fclose(fp);
	
	return EXIT_SUCCESS;

}



