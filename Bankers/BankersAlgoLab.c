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
	int randArr[3];
	for( k = 0; k < 3; k++)
	{
		randArr[0] = rand()%(avail[0]+1);
		randArr[1] = rand()%(avail[1]+1);
		randArr[2] = rand()%(avail[2]+1);
		sleep(rand()%3);
		
		pthread_mutex_lock(&mutex);
		printf("\n\tHello from Consumer: %d",abs((int)(pthread_self())));
		request(abs((int)(pthread_self())),randArr);
		pthread_mutex_unlock(&mutex);
		
	}
	release(abs((int)(pthread_self())));
}

int request(int A,int B[3])
{
	int k,m;
	int bool = 0;
	printf("\nCustomer number is: %d",A);
	printf("\nRequesting %d  %d  %d",B[0],B[1],B[2]);
	for(m = 0; m < 5; m++)
	{
		for(k = 0; k < 3; k++)
		{
			bool = 1;
			if(B[k] <= need[m][k])
			{
				if(B[k] <= avail[m][k])
				{
					avail[m][k] = avail[m][k]-B[k];
					allocation[m][k] = allocation[m][k]+B[k];
					need[m][k] = need[k]-B[k];
					if(checkSafety(avail) == 0)
					{
						
						printf("failed");
						avail[m][k] = avail[m][k]+B[k];
						allocation[m][k] = allocation[m][k]-B[k];
						need[m][k] = need[m][k]+B[k];
						bool = 0;
						break;
					}
					else
					{
						printf("passed");
						break;
					}
				}
				else
				{
					//wait
				}
			}
			else
			{
				break;
				bool = 0;
			}
		}
	}
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

int checkSafety(int[] arr)
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
