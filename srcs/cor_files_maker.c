#include "info.h"

// void	output_stripped_data()
// {

// }

// void	write_cor_file()
// {

// }

void		make_cor_files(t_info *i, int ac, char **av) // test version
{
	int	args_counter;

	args_counter = -1;
	while (++args_counter < ac)
	{
		i->file.name = ft_strdup(av[args_counter]);
		while ((i->file.data = file_get_data(av[args_counter]))
			i->compiled_data = file_compile(i, &i->file);
		// if (i->flags & FLAG_A)
		// 	ft_printf("Output a stripped and annotated version\n");
		// else
		// {
		// 	ft_printf("convert to byte-code\n");
		// 	// i->byte_code = convert_to_byte_code(i->compiled_data);
		// 	// write_cor_file(&i->file);
		// }
		// file_clear(&i->file);
	}
}
