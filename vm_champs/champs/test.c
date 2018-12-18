#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct 		test
{
	char a;
	int b;
} 					t_test;

int main(int ac, char **av)
{
	int fd = open("test", O_APPEND | O_RDWR | O_CREAT);

	printf("fd: %d\n", fd);
	t_test test;

	test.a = 65;
	test.b = COREWAR_EXEC_MAGIC;

	int b = COREWAR_EXEC_MAGIC;
	write(fd, &b, sizeof(b));
	return (0);
}