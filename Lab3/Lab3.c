#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void doFib(int n, int doPrint)
{
    pid_t root_pid = getpid();

    pid_t pid1;
    int status1;

    pid_t pid2;
    int status2;

    if(n < 2) // Base case, exit back to parent?
    {
        exit(n);
    }
    else // if not base case, fork child processes
    {
        pid1 = fork();
        if (pid1 == 0) // Child Process 1 (for fib(n-1))
        {
            doFib(n-1, doPrint);
            status1 = n-1;
            exit(n-1);
        } 
        else if (pid1 > 0) // Parent Process
        {
            pid2 = fork();
            if (pid2 == 0) // Child Process 2 (for fib(n-2))
            {
                doFib(n-2, doPrint);
                status2 = n-2;
                exit(n-2);
            }


            // When to print?
            if (getpid() == root_pid)
            {
                int result =  status1 +  status2;
                if (doPrint)
                {
                    printf("%d\n", result);
                }
                else
                {
                    exit(result);
                }
            }
        }
    }
}


int main()
{
	int input;
	printf("\n\nEnter input: ");
	scanf("%d", &input);

	printf("Length is %d",input);
	return 0;
}


