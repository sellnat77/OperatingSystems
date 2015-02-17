#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
	int input;
	int k = 0;
	printf("Enter input: ");
	scanf("%d", &input);
	pid_t childpid;
	k = 0;

	while(k < input)
	{
		childpid = fork();
		if(childpid < 0)
		{
			exit(-1);
		}
		else if(childpid == 0)
		{	
		}
		else
		{
			wait(NULL);
			printf("\n\nCurrent pid:%d\tppid:%d",getpid(),getppid());
			printf("\tMy child is:%d\n",childpid);
			exit(1);
		}
		k++;
	}
	exit(1);
}

