#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"
# define VALID_SYMBOLS        		"abcdefghijklmnopqrstuvwxyz_0123456789-%,: "
# define FLAG_A 					0b00000001
# define FLAG_M 					0b00000010
# define REG						0b00000001
# define DIR						0b00000010
# define IND						0b00000011
# define VALID	 					2
# define COMMENT_CHAR_ALTER 		';'
# define ENDLINE_CHAR 				'\n'
# define ENDSTRING_CHAR				'\0'
# define QUOTES_CHAR		 		'\"'
# define SPACE_CHAR 				' '
# define MAX_ARGUMENTS				3

typedef enum 				e_errors
{
	E_INVALID_COMMAND = 1,
	E_SEMANTIC_ERROR,
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

typedef struct				s_counter
{
	size_t					column;
	size_t					row;
	size_t					begin_whitespaces;
	size_t					bytes;
}							t_counter;

typedef struct				s_file
{
	int						fd;
	char					*name;
	char					*data;
	char					*line;
	t_header				hdr;
}							t_file;

typedef struct				s_file_cor
{
	t_header				header;
	unsigned int			magic;
	unsigned int		    prog_size;
	// size_t					*bot_size;
	// size_t					*byte_code;
}							t_file_cor;

typedef struct				s_argument
{
	bool					is_active;
	uint8_t					opcode; // reg, ind, dir
	char					*name;
	char					*reference;
	size_t					value;
}							t_argument;

typedef struct				s_instruction
{
	uint8_t					opcode;
	uint8_t					opcode_args;
	char					*name;
	t_argument				arguments[MAX_ARGUMENTS];
	size_t					byte_code;
	uint8_t					size;
}							t_instruction;

typedef struct				s_token
{
	t_list					*labels;
	t_instruction			*instruction;
	size_t					position;
}							t_token;

typedef struct				s_linker_label
{
	t_list					*token;
	size_t					position;
} 							t_linker_label;

typedef struct				s_linker_ref
{
	// t_token					*token;
	char					*reference;
	uint8_t					position;
	// struct s_linker_refs	*next;
} 							t_linker_ref;

typedef struct				s_lists
{
	t_list					*tokens;
	t_list					*labels;
	t_list					*link_labels;
	t_list					*link_refs;
}							t_lists;

void				usage(void); // test version
/*
** MAIN funcitons
*/
uint8_t				flags_analyze(int *ac, char ***av, int *args_counter);
t_file_cor			*file_cor_make(const char *file_name);
int					file_get_line(t_file *file, t_counter *counter);
void				tokenizer(t_file *file, t_lists *lists, t_counter *counter);
size_t				get_currunet_column(t_counter *counter);
/*
** Errors
*/
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
bool				is_comment_cmd(char *str);
void				valid_comment(t_file *file, t_counter *counter);
bool				is_name_cmd(char *str);
void				valid_name(t_file *file, t_counter *counter);
size_t				shift_chars(const char c);
size_t				get_whitespaces(const char *str);
bool				is_whitespaces(const char c);

/*
** Lable_handler
*/
void 			   	append_label(t_list **label_head, char *label);
bool				is_label_without_instruction(char *line, t_counter *counter);
bool				label_exists(char *line);
bool				is_label_char(char c);
char				*new_label(char *line, t_counter *counter);

#endif
