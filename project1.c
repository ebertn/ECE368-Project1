#include <stdio.h>
#include <math.h>
#include "project1.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	
	if(argc != 2 && argc != 5){	
		fprintf(stderr, "Wrong number of arguments for modes 1 or 2");
	}
	
	if(argc == 2){
		mode_2(argv);
	}	
	printf("main test");
    	if(argc == 5){
		mode_1(argv);
	}
	return EXIT_SUCCESS;
}
