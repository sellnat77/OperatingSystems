#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(){
	int input;
	int k = 0;
	//int status = 0;
	printf("Enter input: ");
	scanf("%d", &input);
	pid_t childpid;
/*
	for(k = 0;k < input; k++)
	{
		childpid = fork();
		if(childpid < 0)
		{
			printf("error");
			exit(1);
		}
		else if(childpid == 0)
		{
			printf("Parent(%d): %d\n",k+1,getppid());
			printf("Child (%d): %d\n",k+1,getpid());
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
*/
	childpid = fork();

	if(childpid < 0)
	{
		printf("error");
		exit(1);
	}
	else if(childpid == 0)
	{
		printf("Parent(%d): %d\n",k+1,getppid());
		printf("Child (%d): %d\n",k+1,getpid());
		exit(0);
	}
	else
	{
		wait(NULL);
	}



/*
	
		//childpid = fork();
		printf("\n\nParent id = %d and child id is %d", getppid(), getpid());
		//printf(" Current process id is %d\n", childpid);
		if(childpid < 0){
			exit(0);		
		}
		else if(childpid == 0){
			//printf("\n\nParent id = %d and child id is %d", getppid(), getpid());
			//printf(" Current process id is %d\n", childpid);
			//exit(1);		
		}
		else{
			wait(NULL);
			printf(" Current process id is %d\n", childpid);
			///k++;
			exit(1); 		
		}
	}
*/
	//printf("\n\nParent id = %d and child id is %d", getppid(), getpid());
	//printf(" Current process id is %d\n", getppid());
	exit(0);

}
