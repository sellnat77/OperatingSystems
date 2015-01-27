/****************************************************************/
/* PROGRAM NAME: lab1.c */
/* DESCRIPTION: This lab assignment introduces C syntax and use of */
/* command line arguments */
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>
int main(int argc, char *argv[])
{
	
	int i,j,k,n,max,min,temp;
	double randA[n];
	double sum,avg;
	if (argc !=2)
	{
		printf("\n Usage: Need filename and one argument\n");
		exit(1);
	}
	n = atoi(argv[1]);
	srand(n);
	printf ("\n");
	
	for(k = 0; k < n; k++)
	{
		randA[k] = (rand()%200)-100;
		printf("%2d: %3.2f\n",(k+1),randA[k]);
	}
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(randA[i] > randA[j])
			{
				temp = randA[i];
				randA[i] = randA[j];
				randA[j] = temp;
			}
		}
	}
	for(k = 0; k < n; k++)
	{
		sum += randA[k];
	}
	printf("\nAverage = %3.2f\n",(sum*1.0/n));
	printf("\nMax = %3.2f\n",randA[0]);
	printf("\nMin = %3.2f\n",randA[n]);
	exit(1);
}
