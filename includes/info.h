#ifndef INFO_H
# define INFO_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
// # include "op.h"
# define FLAG_A 0b00000001
# define FLAG_M 0b00000010

typedef struct				s_file
{
	const char				*name;
	char					*data;
}							t_file;

typedef struct				s_info
{
	uint8_t					flags;
	t_file					file;
	unsigned int			*compiled_data;
	unsigned int			*byte_code;
}							t_info;

typedef struct				s_token
{
	uint8_t					args[3];
	char					*label;
	char					*instruction;
	unsigned int			position;
}							t_token;

typedef struct				s_stck_tkns
{
	t_token					token;
	struct s_stack_tokens	*next;
}							t_stck_tkns;

uint8_t     		flags_analyze(int *ac, char ***av);
void				make_cor_files(t_info *info, int ac, char **av);
unsigned int		*file_compile(const t_info *i, const t_file *f);
char				*file_get_data(const char *file_name);
/*
**
** 		 Compiler stages:
**	|	------------------	|
**	|	- Lexical analyz	|
**	|	- Syntax analyz		|
**	|	- Semantic analyz	|
**	|	- Linker			|
**	|	------------------	|
**
*/
unsigned int		*compile_file(const t_info *info, const t_file *file);

/*
**	Lexical analyze
*/
void				lexical_analyze(const t_info *i, const t_file *f,	\
													t_stck_tkns **st);
void				valid_header(char *data, unsigned int *row,			\
													unsigned int *column);
#endif
