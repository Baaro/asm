#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"
# define FLAG_A 				0b00000001
# define FLAG_M 				0b00000010
# define VALID	 				2
# define COMMENT_CHAR_ALTER 	';'
# define ENDLINE_CHAR 			'\n'
# define STRING_QUOTES_CHAR 	'\"'
# define SPACE_CHAR 			' '
# define IS_NAME				0
# define IS_COMMENT				1

typedef enum 				e_errors
{
	INVALID_COMMAND	= 1,
	DOUBLE_NAME,
	DOUBLE_COMMENT,
	SYNTAX_ERROR,
	LEXICAL_ERROR,
	UNKNOWN_COMMAND,
	INVALID_SYMBOLS,
	INVALID_STRING,
	NOT_ALL_CMD,
	CHAMPION_NAME_TOO_LONG,
	NO_BEGIN_QUOTES,
	NO_END_QUOTES,
}							t_errors;

typedef struct				s_file
{
	int						fd;
	char					*name;
	char					*h_name;
	char					*h_comment;
	char					*data;
	char					*line;
}							t_file;

typedef struct				s_file_cor
{
	t_header				header;
	size_t					*bot_size;
	size_t					*byte_code;
}							t_file_cor;

typedef struct				s_counter
{
	size_t					column;
	size_t					row;
}							t_counter;

typedef struct				s_token
{
	char					*label;
	char					*instruction;
	char					*arguments[3];
	struct s_token			*next;
}							t_token;

// typedef struct				s_byte_instrn
// {
// 	uint8_t					instruction;
// 	uint8_t					params;
// 	uint8_t					reg_val;
// 	size_t					dir_val;
// 	size_t					ind_val;				
// 	size_t					stack_position;
// 	size_t					byte_position;
// 	char					*label;
// 	struct s_byte_instrn	*next;
// }							t_byte_instrn;

typedef struct				s_stacks
{
	t_token					*tokens;
	// t_stack_labels		labels;
	// t_stack_referances	labels_ref;
	// t_stack_byte_code	byte_code;
}							t_stacks;

uint8_t				flags_analyze(int *ac, char ***av, int *args_counter);
t_file_cor			*file_cor_make(const char *file_name);
t_token				*tokenizer(t_file *file);
void				valid_header(t_file *file, t_counter *counter);
bool				valid_name(char *line, char **name, t_counter *counter);
bool				valid_comment(char *line, char **comment, t_counter *counter);
char				*get_name(char *line, size_t name_len, t_counter *counter);
char				*get_comment(char *line, size_t comment_len, t_counter *counter);
void				valid_tail_of_string(char *line, size_t after_end_quotes, t_counter *counter);
bool				is_name_cmd(const char *line, t_counter *counter);
bool				is_comment_cmd(const char *line, t_counter *counter);

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
// unsigned int		*compile_file(const t_info *info, const t_file *file);

/*
**	Lexical analyze
*/
// void				lexical_analyze(const t_info *i, const t_file *f,	\
													t_stck_tkns **st);
void				valid_header(t_file *file, t_counter *counter);

#endif
