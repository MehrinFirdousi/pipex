#include <stdio.h>
#include "../include/libft.h"
#include <bsd/string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	char *str = (char *)malloc(20);
	ft_strlcpy(str, "hello", 20);
	printf("1parent, %s\n", str);
	if (fork() == 0)
	{
		printf("1child, %s\n", str);
		ft_strlcpy(str, "byeee", 20);
		printf("2child, %s\n", str);
		free(str);
	}
	else
	{
		wait(NULL);
		printf("2parent, %s\n", str);
		free(str);
	}
	
	return (0);
}