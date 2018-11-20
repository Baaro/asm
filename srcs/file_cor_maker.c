#include "asm.h"

// char		*file_get_data(const char *file_name) // test version
// {
// 	char	*file_data;
// 	char	*file_line;
// 	int		file_fd;

// 	file_data = NULL;
// 	if (ft_is_file(file_name))
// 	{
// 		file_data = ft_strnew(0);
// 		file_fd = open(file_name, O_RDONLY);
// 		while (get_next_line(file_fd, &file_line) == 1)
// 		{
// 			file_data = ft_strjoincl(file_data,
// 						ft_strjoincl(file_line, "\n", 0), 1);
// 		}
// 	}
// 	else
// 		ft_printf("It's not a file: \"%s\"\n", file_name);
// 		// errors(ERROR_IT_IS_NOT_A_FILE);
// 	return (file_data);
// }

void	file_cor_compile(t_file_cor *file_cor, t_file *file) // test version
{
	// t_stacks	stacks;

	// ft_memset(stacks, 0, sizeof(t_stacks));
	stacks.tokens = tokenizer(file);
	stacks.byte_code = byte_code_generator(stacks.tokens);
	// linker(&file_cor->byte_code, stacks.);
	return (NULL);
}

t_file_cor		*file_cor_make(const char *file_name) // test version
{
	t_file		*file;
	t_file_cor	*file_cor;

	file = ft_memalloc(sizeof(t_file));
	file_cor = ft_memalloc(sizeof(t_file_cor));
	file->name = ft_strdup(file_name);
	file->fd = open(file->name, O_RDONLY);
	file_cor_compile(file_cor, file);
	close(file->fd);
	free(file);
	return (file_cor);
}
