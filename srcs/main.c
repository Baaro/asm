#include "asm.h"

void	usage(void) // test version
{
	ft_printf("\nUsage: ./asm [-a] <sourcefile.s>"
			"\n    -a : Instead of creating a .cor file, "
			"outputs a stripped and annotated "
			"version of the code to the standard output.\n");
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	uint8_t		flags;
	t_file_cor	*fc;
	t_file		*f;
	t_counter	*c;

	if (ac == 1)
		usage();
	else if (ac >= 2)
	{
		c = counter_new();
		c->args = 1;
		while (c->args < ac)
		{
			f = file_get(av[c->args]);
			fc = file_cor_make(f, c);
			file_cor_write(fc, flags, c);
			file_del(&f);
			file_cor_del(&fc);
			counter_clear(c);
			c->args++;
		}
		counter_del(&c);
	}
	// system("leaks --hex asm");
	return (EXIT_SUCCESS);
}
