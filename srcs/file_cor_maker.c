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
	t_lists		*lists;
	t_counter	*counter;

	ft_printf("filename: %s\n", file->name);
	counter = ft_memalloc(sizeof(t_counter));
	lists = ft_memalloc(sizeof(t_lists));
	valid_header(file, counter);
	tokenizer(file, lists, counter);
	// link_labels(stacks);
	// make_bytecode(stacks, file_cor);
	ft_printf(".name: %s\n", file->hdr.prog_name);
	ft_printf(".comment: %s\n", file->hdr.comment);
	// ft_printf("DATA: \n%s\n", file->data);
	file_cor = NULL;
	free(lists);
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
		char *slash = ft_strrchr(file_name, '/');
		ft_printf("ERROR: Can't read source file %s\n", ft_strsub(slash + 1, 0, ft_strlen(slash)));
		exit(1);
	}
	file_cor_compile(file_cor, file);
	file_free(&file);
	free(file_cor);
	return (file_cor);
}
