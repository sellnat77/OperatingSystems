#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int avail[3] = {0,0,0};
int max[5][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0}
	};
int need[5][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0}
	};
int allocation[5][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0}
	};

pthread_mutex_t mutex;

void *consume(void *param);
void release(int);
void populateMax(int,int,int);
int request(int,int[]);

int main(int arg, char* argc[]) 
{	
	int k;
	avail[0] = atoi(argc[1]);
	avail[1] = atoi(argc[2]);
	avail[2] = atoi(argc[3]);
	
	populateMax(avail[0],avail[2],avail[2]);
	pthread_t consumerThreads[5];
	
	for(k = 0; k < 5; k++)
	{
		pthread_create(&consumerThreads[k],NULL,consume,NULL);
	}
	
	sleep(10);
	return(0);
}

void *consume(void *param)
{
	int k;
	for( k = 0; k < 3; k++)
	{
		
		sleep(rand()%3);
		
		pthread_mutex_lock(&mutex);
		printf("\n\tHello from Consumer: %d",(int)(pthread_self()));
		request(1,avail);
		pthread_mutex_unlock(&mutex);
		
	}
	release((int)(pthread_self()));
}

int request(int A,int B[])
{
	int bool = 0;
	
	
	
	return(bool);
}

void release(int customerNum)
{
	
}

void populateMax(int limR1,int limR2,int limR3)
{
	int k,m; 
	for(k = 0; k < 5; k++)
	{
		for(m = 0; m < 3; m++)
		{
			max[k][m] = (rand())%(avail[m]+1);
		}
		printf("\nROne: %2d RTwo: %2d RThree: %2d\n",max[k][0],max[k][1],max[k][2]);
	}
}
