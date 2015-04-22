
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
#define BUFFER_SIZE 10

buffer_item buffer[BUFFER_SIZE];
void initialize_buffer();
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
pthread_mutex_t mutex;

sem_t full,empty;

int bufferCounter;



void *producer(void *param);
void *consumer(void *param);


//Main method
int main(int argc, char *argv[]){
	srand(time(NULL));
	int timeOut;
	int producers;
	int consumers;
	
	int k;
	
	if (argc < 2){
		printf("\n Error\n");
		exit(1);
	}
	else{
		timeOut = atoi(argv[1]);
		producers =atoi(argv[2]);
		consumers =atoi(argv[3]);
	}
	pthread_t producerThreads[producers];
	pthread_t consumerThreads[consumers];
	
	printf("TimeOut = %2d producers = %2d consumers = %2d",timeOut,producers,consumers);
	
	initialize_buffer();
	
	for(k = 0; k < producers; k++){

		printf("\n\nCreating producer thread");
		pthread_create(&producerThreads[k],NULL,producer,NULL);

		
	}
	for(k = 0; k < consumers; k++){
		
		printf("\n\nCreating consumer thread");
		pthread_create(&consumerThreads[k],NULL,consumer,NULL);
	
	}
	sleep(timeOut);
	
	exit(0);
}


void *producer(void *param){
	printf("\n\tEntered producer mode");
	buffer_item item;
	
	
	while(1){
		sleep(1);
		item = rand()%201-100;
		
		//GRAB LOCK
		
		
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		
		if(insert_item(item)){
			printf("Producer ERROR");
		}
		else{
			printf("\n\tProducer produced %3d",item);
		}
		//RELEASE LOCK
		pthread_mutex_unlock(&mutex);
		//sem_wait(&sem);
		sem_post(&full);
		
		
	}
	
}


void *consumer(void *param){
	printf("\n\tEntered consumer mode");
	buffer_item item;
	//GRAB LOCK
	
	while(1){
		sleep(2);
		item = rand()%201-100;
		
		
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		
		
		if(remove_item(&item)){
			printf("Consumer ERROR");

		}
		else{
			printf("\n\t\tConsumer consumed %3d",item);

		}
		//RELEASE LOCK
		pthread_mutex_unlock(&mutex);
		//sem_wait(&sem);
		sem_post(&empty);
	}
}

void initialize_buffer(){
	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);
	
	bufferCounter = 0;
	int k; 
	for(k = 0; k < BUFFER_SIZE; k++){
		buffer[k] = 0;
	}
	
}

int insert_item(buffer_item item){
	if(bufferCounter < BUFFER_SIZE){
		buffer[bufferCounter] = item;
		bufferCounter++;
		//int k;
		//for(k = 0; k < BUFFER_SIZE; k++)
		//{
		//	printf("\n%2d.)  %3d",k,buffer[k]);
		//}
		return 0;
	}
	else{
		return -1;
	}
}

int remove_item(buffer_item *item){
	if(bufferCounter > 0){
		*item = buffer[(bufferCounter-1)];
		bufferCounter--;
		return 0;
	}
	else{
		return -1;
	}
}

