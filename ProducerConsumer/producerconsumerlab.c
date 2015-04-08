
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
int remove_item(buffer_item *item);
pthread_mutex_t mutex;

sem_t sem;

int bufferCounter;



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
		timeOut = atoi(argv[1]);
		producers =atoi(argv[2]);
		consumers =atoi(argv[3]);
	}
	pthread_t producerThreads[producers];
	pthread_t consumerThreads[consumers];
	
	printf("TimeOut = %2d producers = %2d consumers = %2d",timeOut,producers,consumers);
	
	for(k = 0; k < producers+consumers; k++)
	{
		if(k < producers)
		{
			printf("\n\nCreating producer thread");
			pthread_create(&producerThreads[k],NULL,(void *)producer,(void *)&buffer);
		}
		if(k < consumers)
		{
			printf("\n\nCreating consumer thread");
			pthread_create(&consumerThreads[k],NULL,(void *)consumer,(void *) &buffer);
		}
		
	}
	/*
	printf("\n\nCreating producer thread");
	pthread_create(&producerThread,NULL,(void *)producer,(void *)&buffer);
	printf("\n\nCreating consumer thread");
	pthread_create(&consumerThread,NULL,(void *)consumer,(void *) &buffer);
	*/
	for(k = 0; k < producers+consumers; k++)
	{
		if(k < producers)
		{
			printf("\n\tStarting producer thread");
			pthread_join(producerThreads[k],NULL);
		}
		if(k < consumers)
		{
			printf("\n\tStarting consumer thread");
			pthread_join(consumerThreads[k],NULL);
		}
		
	}
	
	//pthread_join(producerThread,NULL);
	//pthread_join(consumerThread,NULL);
	sleep(timeOut);
	
	return 0;
}


void *producer(void *param)
{
	printf("\n\tEntered producer mode");
	buffer_item item;
	
	
	while(1)
	{
		sleep(1);
		item = rand()%201-100;
		
		//GRAB LOCK
		pthread_mutex_lock(&mutex);
		
		if(insert_item(item))
		{
			printf("ERROR");
		}
		else
		{
			printf("\n\tProducer produced %3d",item);
		}
		//RELEASE LOCK
		pthread_mutex_unlock(&mutex);
	}
	
}


void *consumer(void *param)
{
	printf("\n\tntered consumer mode");
	buffer_item item;
	//GRAB LOCK
	
	while(1)
	{
		sleep(1);
		item = rand()%201-100;
		
		
		pthread_mutex_lock(&mutex);
		
		if(remove_item(&item))
		{
			printf("ERROR");

		}
		else
		{
			printf("\n\t\tConsumer consumed %3d",item);

		}
		//RELEASE LOCK
		pthread_mutex_unlock(&mutex);
	}
}

void initialize_buffer()
{
	pthread_mutex_init(&mutex,NULL);
	sem_init(&sem,0,5);
	
	bufferCounter = 0;
	int k; 
	for(k = 0; k < BUFFER_SIZE; k++)
	{
		buffer[k] = 0;
	}
	
}

int insert_item(buffer_item item)
{
	if(bufferCounter < BUFFER_SIZE)
	{
		buffer[bufferCounter] = item;
		bufferCounter++;
		return 0;
	}
	else
	{
		return -1;
	}
}

int remove_item(buffer_item *item)
{
	if(bufferCounter > 0)
	{
		*item = buffer[bufferCounter-1];
		bufferCounter--;
		return 0;
	}
	else
	{
		return -1;
	}
}

