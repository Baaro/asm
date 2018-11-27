#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"
# define FLAG_A 					0b00000001
# define FLAG_M 					0b00000010
# define REG						0b00000001
# define DIR						0b00000010
# define IND						0b00000011
# define VALID	 					2
# define COMMENT_CHAR_ALTER 		';'
# define ENDLINE_CHAR 				'\n'
# define ENDSTRING_CHAR				'\0'
# define STRING_QUOTES_CHAR 		'\"'
# define SPACE_CHAR 				' '
# define MAX_ARGUMENTS				3

typedef enum 				e_errors
{
	E_INVALID_COMMAND = 1,
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

typedef struct				s_argument
{
	uint8_t					type; // reg, ind, dir
	char					*reference;
	size_t					value;
}							t_argument;

typedef struct				s_instruction
{
	uint8_t					type;
	t_argument				arguments[MAX_ARGUMENTS];
	uint8_t					size;
}							t_instruction;

typedef struct				s_label
{
	char					*label;
	struct s_label			*next;
}							t_label;

typedef struct				s_token
{
	t_label					*labels;
	t_instruction			instruction;
	size_t					position;
	struct s_token			*next;
}							t_token;

typedef struct				s_linker_label
{
	t_token					*token;
	size_t					position;
	struct s_linker_labels	*next;
} 							t_linker_label;

typedef struct				s_linker_ref
{
	t_token					*token;
	uint8_t					position;
	struct s_linker_refs	*next;
} 							t_linker_ref;

typedef struct				s_stacks
{
	t_token					*tokens;
	t_linker_label			*l_labels;
	t_linker_ref			*l_refs;
}							t_stacks;

void				usage(void); // test version
uint8_t				flags_analyze(int *ac, char ***av, int *args_counter);
t_file_cor			*file_cor_make(const char *file_name);
void				tokenizer(t_file *file, t_stacks *stacks, t_counter *counter);

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
bool				valid_commands(t_file *file, t_counter *counter);
char				*get_name(char *line, size_t name_len, t_counter *counter);
char				*get_comment(char *line, size_t comment_len, t_counter *counter);
void				valid_tail_of_string(char *line, size_t after_end_quotes, t_counter *counter);
size_t				shift_chars(char c);
size_t				shift_whitespaces(const char *str);
bool				is_whitespaces(const char c);
int					file_get_line(t_file *file);
#endif
