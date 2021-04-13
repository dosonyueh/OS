#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SEQUENCE 10
typedef struct{
	long fib_sequence[MAX_SEQUENCE];
	int sequence_size;
}share_data;

int main()
{
	

}
