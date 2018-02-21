#include<stdio.h>
#include<math.h> 
#include "project1.h"

int main(int argc, char** argv){
	if(argc == 2){
		mode_2(argv);
	}
	if(argc == 5){
		mode_1(argv);
	}

	/*FILE *fp = fopen(argv[1], "r");

	Task *head = NULL;

	read_input(fp, &head);
	print_queue(stdout,head);
	free_queue(head);
	fclose(fp);*/

	return EXIT_SUCCESS;
}
