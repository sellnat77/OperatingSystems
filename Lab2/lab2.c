/*Name: Russell Tan
 *           011529945
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
	int input;
	int k = 0;
	printf("\n\nEnter input: ");
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
		else if(childpid>0)
		{
			wait(NULL);
			printf("\n\n\tppid:%d\tCurrent pid:%d\tMy Child is:%d\n",getppid(),getpid(),childpid);
			exit(1);
		}
		k++;
	}
	printf("\n\n\tppid:%d\tCurrent pid:%d\tMy Child is:%d\n",getppid(),getpid(),childpid);
	exit(1);
}

