#include "./includes/asm.h"
#include <stdio.h>
#define BUFFER 100

size_t get_size(int fd)
{
	ssize_t 	ret;
	size_t		size;
	size_t		*data;

	size = 0;
	while (true)
	{
		data = ft_memalloc(BUFFER);
		ret = read(fd, data, BUFFER);
		if (ret == 0)
			break ;
		if (ret == -1)
		{
			printf("wrong ret: %zd\n", ret);
			exit(1);
		}
		size += (size_t)ret;
		free(data);
	}
	return (size);
}

int main(int argc, char **argv)
{
	int		fd1 = open(argv[1], O_RDONLY, S_IRUSR);
	size_t	size1 = get_size(fd1);
	unsigned char	*data1 = ft_memalloc(size1);
	read(fd1, data1, size1);
	
	printf("argv1: %s\n", argv[1]);
	printf("size1: %zu\n", size1);
	size_t counter1 = 0;
	while (counter1 < size1)
	{
		printf("data1: %zd\n", data1[counter1]);
		counter1++;
	}

	int		fd2 = open(argv[2], O_RDONLY, S_IRUSR);
	size_t	size2 = get_size(fd2);
	unsigned char	*data2 = ft_memalloc(size2);
	read(fd2, data2, size2);
	printf("argv2: %s\n", argv[2]);
	printf("size2: %zu\n", size2);
	size_t counter2 = 0;
	while (counter2 < size2)
	{
		printf("data2: %zd\n", data2[counter2]);
		counter2++;
	}
	// if (size1 == size2)
	// {
	// 	counter = 0;
	// 	while (++counter < size2)
	// 	{
	// 		if (data1[counter] != data2[counter])
	// 		{
	// 			printf("data1: %zu != data2: %zu\nposition:%zu\n\n", data1[counter], data2[counter], counter);
	// 		}
	// 		printf("data1: %zu data2: %zu\nposition:%zu\n\n", data1[counter], data2[counter], counter);
	// 		counter++;
	// 	}
	// 	printf("SUCCESS! BOTH FILES ARE EQUAL!\n");
	// }
	// else
	// 	printf("SIZE IS NOT EQUAL!\n");
	return (0);
}