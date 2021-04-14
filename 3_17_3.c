#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SEQUENCE 10
typedef struct{
	long fib_sequence[MAX_SEQUENCE];
	int sequence_size;
}shared_data;

int main()
{
	shared_data data;
	const int Size = sizeof(shared_data);
	const char *name = "OS";
	scanf("%d",&data.sequence_size);
	if(data.sequence_size > 10 || data.sequence_size < 0)
	{
		printf("invaild parameter!\n");
		return 1;
	}
	int shm_fd;
	void *ptr;
	shm_fd = shm_open(name,O_CREAT | O_RDWR,0666);
	ftruncate(shm_fd,Size);
	ptr = mmap(0,Size,PROT_WRITE,MAP_SHARED,shm_fd,0);
	sprintf(ptr,"%d",data.sequence_size);
	pid_t pid;
	pid = fork();

	if(pid < 0)
	{
		fprintf(stderr,"fork failed\n");
		return 1;
	}
	else if(pid == 0)
	{
		printf("into child process\n");
		shm_fd = shm_open(name,O_RDWR,0666);
		ptr = mmap(0,Size,PROT_WRITE,MAP_SHARED,shm_fd,0);
		int number = atoi(ptr);
		long fib_seq[10];
		fib_seq[0]=0;
		fib_seq[1]=1;
		for(int i = 2 ; i< number;i++)
			fib_seq[i] = fib_seq[i-1]+fib_seq[i-2];
		for(int i = 0 ; i < number; i++)
		{
			sprintf(ptr, "%ld ",fib_seq[i]);
			if(fib_seq[i] < 10)
				ptr += 2;
			else 
				ptr += 3;
		}
		printf("child process end\n");

	}
	else
	{
		wait(NULL);
		shm_fd = shm_open(name,O_RDONLY,0666);
		ptr = mmap(0,Size,PROT_READ,MAP_SHARED,shm_fd,0);
		printf("%s\n",(char*)ptr);
		shm_unlink(name);
	}
}
