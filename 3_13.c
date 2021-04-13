#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num,i;
	scanf("%d",&num);
	int Fib[num];
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		fprintf(stderr,"Fork Failed\n");
		return 1;
	}
	else if(pid == 0)
	{
		if(num<0)
		{
			printf("num is negative number\n");
			return 1;
		}
		Fib[0] = 0;
		Fib[1] = 1;
		for(i = 2 ; i < num;i++)
		{
			Fib[i] = Fib[i-1] + Fib[i-2];
		}
		for(i = 0 ; i<num;i++)
			printf("%d\n",Fib[i]);
	}
	else
	{
		wait(NULL);
		printf("child Complete\n");
	}

}
