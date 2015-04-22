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

void consume();
void release();
void populateMax(int,int,int);
int request(int,int,int);

int main(int arg, char* argc[]) 
{	
	avail[0] = atoi(argc[1]);
	avail[1] = atoi(argc[2]);
	avail[2] = atoi(argc[3]);
	
	populateMax(avail[0],avail[2],avail[2]);
	return(0);
}

void consume()
{
	int k;
	for( k = 0; k < 3; k++)
	{
		sleep(rand()*3);
		request(rand()*avail[0],rand()*avail[1],rand()*avail[2]);
	}
	release();
}

void release()
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
		/*
		max[k][0] = (rand())%limR1;
		max[k][1] = (rand())%limR2;
		max[k][2] = (rand())%limR3;
		*/
		printf("\nROne: %2d RTwo: %2d RThree: %2d\n",max[k][0],max[k][1],max[k][2]);
	}
}

int request(int A,int B,int C)
{
	int bool = 1;
	
	
	
	
	
	
	
	exit(bool);
}
