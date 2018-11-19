#include "info.h"

char		*file_get_data(const char *file_name) // test version
{
	char	*file_data;
	char	*file_line;
	int		file_fd;

	file_data = NULL;
	if (ft_is_file(file_name))
	{
		file_data = ft_strnew(0);
		file_fd = open(file_name, O_RDONLY);
		while (get_next_line(file_fd, &file_line) == 1)
		{
			file_data = ft_strjoincl(file_data,
						ft_strjoincl(file_line, "\n", 0), 1);
		}
	}
	else
		ft_printf("It's not a file: \"%s\"\n", file_name);
		// errors(ERROR_IT_IS_NOT_A_FILE);
	return (file_data);
}

unsigned int	*file_compile(const t_info *i, const t_file *f) // test version
{
	t_stck_tkns		*st;
	unsigned int	*compiled_data;

	compiled_data = NULL;
	lexical_analyze(i, f, &st);
	// syntax_and_semantic_analyzes(st);
	// linker();
	return (compiled_data);
}

// void			clear_file(t_file *file)
// {

// }
