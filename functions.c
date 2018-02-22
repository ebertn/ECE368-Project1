#include <stdio.h>
#include <math.h>

#include "project1.h"

int generate_rate(double inputRate)// inputRate is either lambda or Mu
{
  // Randomly Generates an exponential service rate based on the formula
  int random_value = rand();
  float unit_rand = random_value / (double) RAND_MAX;
  return ceil((-1/ inputRate) * log(1-unit_rand));         //This is similar to slide 10 in Week 3 notes
}

void read_input(FILE *fp, Task **queue){
	fseek(fp, 0L, SEEK_SET);//file starts at the beginning;
	while(!feof(fp)){
		Task *new_task = malloc(sizeof(*new_task));//get memory for new task node
        new_task->num_subtasks = 0;
        new_task->arrival_time = 0;
        new_task->priority = 0;
        //new_task->subtasks = {0};
		fscanf(fp,"%d %d %d ", &(new_task -> arrival_time), &(new_task -> priority), &(new_task ->num_subtasks));
		for(int i = 0; i < new_task->num_subtasks; i++){
			fscanf(fp,"%d ", &(new_task -> subtasks[i]));
            printf("%d\n", new_task->subtasks[i]);
		}

		enqueue(queue, new_task, &cmp_pre_arrival);//push new task node onto the queue
	}
    print_queue(stdout, *queue);
}

void mode_2(char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
	Task* head = NULL;
	//read in file and create queue
	read_input(fp, &head);
    //print_queue(stdout, head);
    fclose(fp);

    simulation(&head);
}

void mode_1(char *argv[]){
	double lam0 = atof(argv[1]); //first arrival time
	double lam1 = atof(argv[2]);//arrivl time
	double mu = atof(argv[3]); //service time
	int num_tasks = atoi(argv[4]);//number of tasks to be performed for both 1's and 0's
	Task *head = generate_queue(lam0,lam1,mu, num_tasks); //generates both queues

    simulation(&head);
}

Task* generate_queue(double lam0, double lam1, double mu, int num){
    Task* queue = NULL;

    // Generate 0s
    for(int i = 0; i < num; i++){
        Task *new_task = malloc(sizeof(*new_task));
    	if(new_task == NULL) { return NULL; }
    	new_task->arrival_time = generate_rate(lam0);
        new_task->priority = 0;
        new_task->num_subtasks = generate_subtasks(mu, new_task->subtasks);
        enqueue(&queue, new_task, &cmp_pre_arrival);
    }

    // Generate 1s
    for(int i = 0; i < num; i++){
        Task *new_task = malloc(sizeof(*new_task));
    	if(new_task == NULL) { return NULL; }
    	new_task->arrival_time = generate_rate(lam1);
        new_task->priority = 1;
        new_task->num_subtasks = generate_subtasks(mu, new_task->subtasks);
        enqueue(&queue, new_task, &cmp_pre_arrival);
    }

    return queue;
}

int generate_subtasks(double mu, int* subtasks){
    int num_subtasks = rand() % 32 + 1;

    for(int i = 0; i < num_subtasks; i++){
        subtasks[i] = generate_rate(mu);
    }

    return num_subtasks;
}

//running average of qlen ("queue length)
int average_qlen(Task** queue){
	Task* cur = *queue;
    int sum = 0;
	while(cur != NULL)// && cur->next != NULL)//find the length of the current queue and add that to the current running total
	{
		cur = cur->next;
        sum += 1;
	}

    return sum;
}

// Returns the number of servers avaliable
int num_avaliable_servers(int t, int* service_finished_times){
    int count = 0;
    for(int i = 0; i < NUM_SERVERS; i++){
        if(service_finished_times[i] <= t){ // If a server is avaliable
            count++;
        }
    }
    printf("Num servers: %d\n", count);
    return count;
}

// Returns the next eligible task in the queue
Task* find_next_task(Task** post_queue, int num_servers){
    if((*post_queue) == NULL){ return NULL; }
    if((*post_queue)->num_subtasks <= num_servers){
        return queue_pop(post_queue);
    }
    Task* cur = *post_queue;
    Task* prev = cur;
    while(cur != NULL){
        if(cur->num_subtasks <= num_servers){
            prev->next = cur->next;
            cur->next = NULL;

            //queue_pop(&cur);
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}

// Controller for the simulation
void simulation(Task** pre_queue){
    int t = 0;
    int num0 = 0, num1 = 0;
    int sum0 = 0, sum1 = 0;
    int qlen_sum = 0;
    int cpu_util = 0;
    Task* post_queue = NULL;
    //int service_finished_time = 0;
    int service_finished_times[64] = {0};

    while(!is_empty(*pre_queue) || !is_empty(post_queue) || num_avaliable_servers(t, service_finished_times) < 64){ // There are still tasks
        printf("t = %d\n", t);
        Task* next = NULL; //queue_pop(pre_queue);

        while(*pre_queue != NULL && (*pre_queue)->arrival_time <= t){
            next = queue_pop(pre_queue);
            enqueue(&post_queue, next, &cmp_post_arrival);
        }

        printf("Post queue: ");
        print_queue(stdout, post_queue);
        serve(&post_queue, service_finished_times, t, &sum0, &sum1, &num0, &num1);

        //cpu_util += service_finished_time <= t; // TODO: baby come back

        if(post_queue != NULL){
            qlen_sum += average_qlen(&post_queue);
        }

        t++;
    }

    printf("Finish time = %d\n", t);

    // Calculate average time in queue
    double av_wait0 = sum0 / ((double) num0);
    double av_wait1 = sum1 / ((double) num1);

    printf("average_wait_0 = %lf\n", av_wait0);
	printf("average_wait_1 = %lf\n", av_wait1);

    // Calculate average queue length
    double av_qlen = qlen_sum / ((double) t);

    printf("average_queue_length = %lf\n", av_qlen);

    // Calculate cpu utilization
    double av_cpu_util = 1 - cpu_util / ((double) t);

    printf("average_CPU_utilization = %lf\n", av_cpu_util);
}

void serve(Task** post_queue, int* service_finished_times, int t, int* sum0, int* sum1, int* num0, int* num1){
    printf("------------------------------------\n");

    int num_servers = num_avaliable_servers(t, service_finished_times);
    Task* next_valid = NULL;
    if(num_servers > 0){
        next_valid = find_next_task(post_queue, num_servers);
    }
    while(num_servers > 0 && next_valid != NULL){
        print_queue(stdout, *post_queue);
        int cpu_util = 0;

        // Pop and free next task
        //Task* served_task = queue_pop(post_queue);

        int subtask_index = 0; // Running count of subtasks that have been served

        for(int i = 0; i < NUM_SERVERS; i++){
            if(service_finished_times[i] <= t && subtask_index < next_valid->num_subtasks){ // If a server is avaliable
                //When the server will finished serving
                service_finished_times[i] = t + next_valid->subtasks[subtask_index];
                subtask_index++;
            }
        }

        printf("----> %d\n", subtask_index);

        // //Sum time in queue, to find average
        // switch(next_valid->priority){
        //     case 0: (*num0)++;
        //             *sum0 += t - served_task->arrival_time; // TODO: change to work with subtasks
        //             break;
        //     case 1: (*num1)++;
        //             *sum1 += t - served_task->arrival_time;
        //             break;
        // }

        free(next_valid);
        num_servers = num_avaliable_servers(t, service_finished_times);
        next_valid = find_next_task(post_queue, num_servers);
    }
}
