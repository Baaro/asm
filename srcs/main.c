#include "info.h"

void	usage(void) // test version
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("    -a : Instead of creating a .cor file, ");
	ft_printf("outputs a stripped and annotated ");
	ft_printf("version of the code to the standard output\n");
}

void	info_init(t_info *i)
{
	ft_memset(i, 0, sizeof(t_info));
	ft_memset(&i->file, 0, sizeof(t_file));
}

int		main(int ac, char **av)
{
	t_info	i;

	if (ac == 1)
		usage();
	else if (ac >= 2)
	{
		info_init(&i);
		i.flags = flags_analyze(&ac, &av);
		make_cor_files(&i, ac, av);
	}
	// system("leaks asm");
	return (0);
}
