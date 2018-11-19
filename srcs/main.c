#include "asm.h"

void	usage(void) // test version
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("    -a : Instead of creating a .cor file, ");
	ft_printf("outputs a stripped and annotated ");
	ft_printf("version of the code to the standard output\n");
}

// void	file_cor_write(t_file_cor file_cor, uint8_t flags)
// {

	// if (i->flags & FLAG_A)
	// 	ft_printf("Output a stripped and annotated version\n");
	// else
	// {
	// 	ft_printf("convert to byte-code\n");
	// 	// i->byte_code = convert_to_byte_code(i->compiled_data);
	// 	// write_cor_file(&i->file);
	// }
	// file_clear(&i->file);
// }

int		main(int ac, char **av)
{
	uint8_t		flags;
	int			args_counter;
	t_file_cor	*file_cor;

	if (ac == 1)
		usage();
	else if (ac >= 2)
	{
		flags = flags_analyze(&ac, &av, &args_counter);
		while (++args_counter < ac)
		{
			file_cor = file_cor_make(av[args_counter]);
			file_cor_write(file_cor, flags);
		}
	}
	// system("leaks asm");
	return (0);
}
