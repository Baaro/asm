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
# define ENDSTRING_CHAR			'\0'
# define STRING_QUOTES_CHAR 	'\"'
# define SPACE_CHAR 			' '

typedef enum 				e_errors
{
	E_INVALID_COMMAND	= 1,
	E_DOUBLE_NAME,
	E_DOUBLE_COMMENT,
	E_UNMATCHED_COMMAND,
	E_INVALID_SYMBOLS,
	E_INVALID_STRING,
	E_NOT_ALL_COMMAND,
	E_CHAMPION_NAME_TOO_LONG,
	E_CHAMPION_COMMENT_TOO_LONG,
	E_NO_BEGIN_QUOTES,
	E_NO_END_QUOTES,
	E_WRONG_TAIL_OF_STRING,
	E_COMMAND_READ,
	E_IS_NOT_ENOUGH_DATA,
	E_WRONG_INPUT,
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
	uint8_t					params;
	uint8_t					reg;
	uint16_t				ind;
	uint32_t				dir;
	uint8_t					size;
	uint8_t					instruction;
	size_t					position;
	char					*label;
	struct s_token			*next;
}							t_token;

typedef struct				s_stacks
{
	t_token					*tokens;
	// t_stack_labels		labels;
	// t_stack_referances	labels_ref;
	// t_stack_byte_code	byte_code;
}							t_stacks;

void				usage(void); // test version
uint8_t				flags_analyze(int *ac, char ***av, int *args_counter);
t_file_cor			*file_cor_make(const char *file_name);
t_token				*tokenizer(t_file *file);

void    			lexical_errors(t_errors error, char *line, t_counter *counter);
void				syntactic_errors(t_errors error, char *line, t_counter *counter);
void    			semantic_errors(t_errors error, char *line, t_counter *counter);
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

void				valid_header(t_file *file, t_counter *counter);
void				valid_commands(t_file *file, t_counter *counter, size_t *h_cmds);
char				*get_name(char *line, size_t name_len, t_counter *counter);
char				*get_comment(char *line, size_t comment_len, t_counter *counter);
void				valid_tail_of_string(char *line, size_t after_end_quotes, t_counter *counter);
size_t				shift_chars(char c);
size_t				shift_whitespaces(const char *str);
bool				is_whitespaces(const char c);
char				*append_data(char *data, char *line);
#endif
