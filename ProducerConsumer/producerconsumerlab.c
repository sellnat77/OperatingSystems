
/* Lab 5 - Producers and consumers
 * 
 * Russell Tan
 * ID: 011529945
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];
void initialize_buffer();
int insert_item(buffer_item item);
int remove_item(buffer_item item);
pthread_mutex_t mutex;



void *producer(void *param);
void *consumer(void *param);


//Main method
int main(int argc, char *argv[])
{
	int timeOut;
	int producers;
	int consumers;
	
	int k;
	if (argc < 2)
	{
		printf("\n Error\n");
		exit(1);
	}
	else
	{
		timeOut = strtol(argv[1],NULL,0);
		producers = strtol(argv[2],NULL,0);
		consumers = strtol(argv[3],NULL,0);
	}
	pthread_t producerThreads[producers];
	pthread_t consumerThreads[consumers];
	
	printf("TimeOut = %2d producers = %2d consumers = %2d",timeOut,producers,consumers);
	
	for(k = 0; k < producers; k++)
	{
		printf("\n\nCreating producer thread");
		pthread_create(&producerThreads[k],NULL,(void *)producer,NULL);
		//pthread_join(producerThreads[k],NULL);
	}
	
	for(k = 0; k < producers; k++)
	{
		pthread_join(producerThreads[k],NULL);
	}
	for(k = 0; k < consumers; k++)
	{
		printf("\n\nCreating consumer thread");
		//pthread_create(&consumerThreads[k],NULL,(void *)consumer,(void *) &timeOut);
		//pthread_join(consumerThreads[k],NULL);
	}
	
	
	
	return 0;
}


void *producer(void *param)
{
	printf("\n\tEntered producer mode");
	buffer_item item;
	//GRAB LOCK
	pthread_mutex_lock(&mutex);
	while(1)
	{
		sleep(1);
		item = rand()%201-100;
		if(insert_item(item))
		{
			printf("ERROR");
		}
		else
		{
			printf("Producer produced %3d",item);
		}
	}
	//RELEASE LOCK
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}


void *consumer(void *param)
{
	printf("Entered consumer mode");
	buffer_item item;
	//GRAB LOCK
	pthread_mutex_lock(&mutex);
	while(1)
	{
		sleep(1);
		item = rand()%201-100;
		if(remove_item(item))
		{
			printf("ERROR");
		}
		else
		{
			printf("Consumer consumed %3d",item);
		}
	}
	//RELEASE LOCK
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

void initialize_buffer()
{
	pthread_mutex_init(&mutex,NULL);
	int k; 
	for(k = 0; k < BUFFER_SIZE; k++)
	{
		buffer[k] = 0;
	}
	
}

int insert_item(buffer_item item)
{
	int k;
	for(k = 0; k < BUFFER_SIZE; k++)
	{
		if(buffer[k] == 0)
		{
			buffer[k] = item;
			return 0;
		}
	}
	
	return -1;
}

int remove_item(buffer_item item)
{
	int k;
	for(k = BUFFER_SIZE-1; k >= 0; k--)
	{
		if(buffer[k] != 0)
		{
			buffer[k] = 0;
			return 0;
		}
	}
	return -1;
}

