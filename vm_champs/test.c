#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct 		test
{
	char a;
	int b;
} 					t_test;

int main()
{
	int b = COREWAR_EXEC_MAGIC;

	//fd
	int fd = open("test", O_APPEND|O_RDWR|O_CREAT, S_IRWXU);
	printf("fd: %d\n", fd);
	write(fd, &b, sizeof(b));
	close(fd);

	//fd1
	int fd1 = open("test1", O_APPEND|O_RDWR|O_CREAT | S_IRWXU);
	printf("fd1: %d\n", fd1);
	write(fd1, &b, sizeof(b));
	close(fd1);

	return (0);
}