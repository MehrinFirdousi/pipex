#include <stdio.h>
#include <fcntl.h>

int main()
{
	printf("hi\n");
	if (open("testfile", O_CREAT, 0700) > 0)
		printf("file created\n");
}