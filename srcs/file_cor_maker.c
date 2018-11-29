#include "asm.h"

void			file_free(t_file **file)
{
	free((*file)->name);
	free((*file)->data);
	free((*file)->line);
	free(*file);
}

t_file			*file_new(void)
{
	t_file		*file;

	file = ft_memalloc(sizeof(t_file));
	ft_memset(&file->hdr, 0, sizeof(t_header));
	return (file);
}

t_file_cor		*file_cor_new(void)
{
	t_file_cor	*file_cor;

	file_cor = ft_memalloc(sizeof(t_file));
	return (file_cor);
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
	ft_printf(".name: %s\n", file->hdr.prog_name);
	ft_printf(".comment: %s\n", file->hdr.comment);
	// ft_printf("DATA: \n%s\n", file->data);
	free(stacks);
	free(counter);
}

t_file_cor		*file_cor_make(const char *file_name) // test version
{
	t_file		*file;
	t_file_cor	*file_cor;

	file = file_new();
	file_cor = file_cor_new();
	file->name = ft_strdup(file_name);
	file->fd = open(file->name, O_RDONLY);
	if (!ft_is_file(file->name))
	{
		char *pos = ft_strrchr(file_name, '/');
		ft_printf("ERROR: Can't read source file %s\n", ft_strsub(pos + 1, 0, ft_strlen(pos)));
		exit(1);
	}
	file_cor_compile(file_cor, file);
	file_free(&file);
	free(file_cor);
	return (file_cor);
}
