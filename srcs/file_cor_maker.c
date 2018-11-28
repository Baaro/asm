#include "asm.h"

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
	// tokenizer(file, stacks, counter);
	ft_printf(".name: %s\n", file->h_name);
	ft_printf(".comment: %s\n", file->h_comment);
	// ft_printf("DATA: \n%s\n", file->data);
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
