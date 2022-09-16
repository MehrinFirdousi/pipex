#include <stdio.h>
#include "../include/libft.h"
#include <bsd/string.h>

int main(int argc, char **argv)
{
	// char res1[4];
	// res1[0] = '/';
	// char *str1 = "";
	// printf("real - %ld\n", strlcat(res1, str1, 4));
	// printf("real - %s\n", res1);

	char res[4];
	res[0] = '/';
	printf("mine - %ld\n", ft_strlcat(res, "", 4));
	printf("mine - %s\n", res);

	return (0);
}