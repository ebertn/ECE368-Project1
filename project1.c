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

    return EXIT_SUCCESS;
}
