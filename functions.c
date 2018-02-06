#include <stdio.h> 
#include <math.h>
// File for our functions

double generate_rate(double InputRate) //InputRate is Lambda or Mu
{
	//generates random numbers
	double random_value = rand();
	double unit_rand = random_value / (double)RAND_MAX;
	return((-1/InputRate) * log(1 - unit_rand));
}


void read_input(FILE *fp, Task **queue )
{
	fseek(fp, 0L, SEEK_SET);//file starts at the beginning; 

	while(fp != EOF)
	{
		//create TASK node 
		if(fp != '\n')
		{
			Task *new_task = malloc(sizeof(*new_task);//get memory for new task node	
			Task *queue_push(queue, new_task);//push new task node onto the queue
			fscanf("%lf%lf%lf", &new_task.arrival_time, &new_task.priority, &new_task.service_time);//scan in data
		}	

	}

}

//start an arrival process
void proccess_task(&queue, int *line, *time, int *server)
{
	while(queue != NULL);
	{
		if(*server != 1)
		{
						  
		
	}		
