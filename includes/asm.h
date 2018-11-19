#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"
# define FLAG_A 0b00000001
# define FLAG_M 0b00000010

typedef struct				s_file
{
	int						fd;
	char					*name;
	char					*data;
	char					*line;
}							t_file;

typedef struct				s_file_cor
{
	t_header				header;
	size_t					*bot_size;
	size_t					*byte_code;
}							t_file_cor;

/*
**
**
*/

typedef struct				s_token
{
	char					*label;
	char					*instruction;
	char					*arguments[3];
	struct s_token			*next;
}							t_token;

typedef struct				s_label
{
	char					*name;
	size_t					position;
}							t_label;

typedef struct				s_referance
{
	char					*name;
	size_t					position;
}							t_referance;

typedef struct				s_stack_tokens
{
	t_token					*top;
	t_token					*bot;
	size_t					size;
}							t_stack_tokens;

typedef struct				s_stack_labels
{
	t_label					*top;
	t_label					*bot;
	size_t					size;
}							t_stack_labels;

typedef struct				s_stack_referances
{
	t_label					*top;
	t_label					*bot;
	size_t					size;
}							t_stack_referances;

typedef struct				s_stacks
{
	t_stack_tokens			tokens;
	t_stack_labels			labels;
	t_stack_referances		labels_ref;
	// t_stack_byte_code		byte_code;
}							t_stacks;

uint8_t				flags_analyze(int *ac, char ***av, int *args_counter);
void				file_cor_make(const char *file_name);
unsigned int		*file_compile(const int file_fd);
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
