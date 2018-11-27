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

void			file_free(t_file **file)
{
	free((*file)->name);
	free((*file)->h_name);
	free((*file)->h_comment);
	free((*file)->data);
	free((*file)->line);
	free(*file);
}

void			file_cor_compile(t_file_cor *file_cor, t_file *file) // test version
{
	t_stacks	*stacks;
	t_counter	*counter;

	ft_printf("filename: %s\n", file->name);
	stacks = ft_memalloc(sizeof(t_stacks));
	counter = ft_memalloc(sizeof(t_counter));
	valid_header(file, counter);
	tokenizer(file, stacks, counter);
	ft_printf(".name: %s\n", file->h_name);
	ft_printf(".comment: %s\n", file->h_comment);
	// ft_printf(".data: %s\n", file->data);
	free(stacks);
	free(counter);
}

t_file_cor		*file_cor_make(const char *file_name) // test version
{
	t_file		*file;
	t_file_cor	*file_cor;

	file = ft_memalloc(sizeof(t_file));
	file_cor = ft_memalloc(sizeof(t_file_cor));
	file->name = ft_strdup(file_name);
	file->fd = open(file->name, O_RDONLY);
	if (!ft_is_file(file->name))
		usage();
	file_cor_compile(file_cor, file);
	file_free(&file);
	free(file_cor);
	return (file_cor);
}
