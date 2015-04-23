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

void *consume(int *param);
void release(int);
void populateMax(int,int,int);
int request(int,int[]*);
int number=0;

int main(int arg, char* argc[]) 
{	
	int k;
	srand(time(NULL));
	avail[0] = atoi(argc[1]);
	avail[1] = atoi(argc[2]);
	avail[2] = atoi(argc[3]);
	
	populateMax(avail[0],avail[2],avail[2]);
	pthread_t consumerThreads[5];
	
	for(k = 0; k < 5; k++)
	{
		pthread_create(&consumerThreads[k],NULL,consume,(int *)k);
	}
	
	sleep(10);
	return(0);
}

void *consume(int *param)
{
	int k;
	int randArr[3];
	for( k = 0; k < 3; k++)
	{
		randArr[0] = rand()%(avail[0]+1);
		randArr[1] = rand()%(avail[1]+1);
		randArr[2] = rand()%(avail[2]+1);
		sleep(rand()%3);
		
		pthread_mutex_lock(&mutex);
		printf("\n\tHello from Consumer: %d",*param);
		request(*param,randArr);
		pthread_mutex_unlock(&mutex);
		
	}
	release(*param);
}

int request(int A,int (*B)[3])
{
	
	int k,m;
	int bool = 0;
	printf("\nCustomer number is: %d",A);
	printf("\nRequesting %d  %d  %d",B[0],B[1],B[2]);

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

int checkSafety(int arr[])
{
	int k;
	for(k = 0; k < 3; k++)
	{

		if(arr[k] < 0)
		{
			return 0;
		}
		
	}
	return 1;
}
