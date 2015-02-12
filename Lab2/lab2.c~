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
	k = 0;
	printf("\tOriginal(%d): %d\n\n",k+1,getppid());
	while(k < input)
	{
		childpid = fork();
		if(childpid < 0)
		{
			printf("error");
			exit(1);
		}
		else if(childpid == 0)
		{
			
			printf("Child pid:%d ppid:%d\n",getpid(),getppid());
			childpid = fork();
			printf("Childs child pid:%d ppid:%d\n",getpid(),getppid());
			exit(0);
		}
		else
		{
			printf("\n\nParent pid:%d ppid:%d\n",getpid(),getppid());
			printf("\tMy child is:%d\n",childpid);
			wait(NULL);
		}
		k++;
	}
/*
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

*/

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

