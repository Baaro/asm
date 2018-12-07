#include "asm.h"

// static char		*file_get_data(int fd)
// {
// 	char	*line;
// 	char	*data;
// 	int		status;

// 	line = NULL;
// 	data = NULL;
// 	while ((status = get_next_line(fd, &line) == 1))
// 		file_append_data(&data, line);
// 	if (status == -1)
// 		lexical_errors(E_WRONG_INPUT, line, NULL);
// 	return (data);
// }

static t_file	*file_new(void)
{
	return (ft_memalloc(sizeof(t_file)));
}

void			file_del(t_file **f)
{
	free((*f)->name);
	free((*f)->data);
	free(*f);
}

t_file			*file_get(char *filename)
{
	t_file	*file;

	if (!ft_is_file(filename))
	{
		char *slash = ft_strrchr(filename, '/');
		ft_printf("ERROR: Can't read source file %s\n", ft_strsub(slash + 1, 0, ft_strlen(slash)));
		exit(1);
	}
	file = file_new();
	file->name = ft_strdup(filename);
	file->fd = open(file->name, O_RDONLY);
	// file->data = file_get_data(file->fd);
	return (file);
}
