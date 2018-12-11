#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"
# define FLAG_A 					1
# define FLAG_M 					2
# define INSTR_CHARS				"abcdefghijklmnopqrstuvwxyz"
# define NUM_INSTRUCTIONS			16
# define VALID	 					2
# define COMMENT_CHARS		 		";#"
# define COMMENT_CHAR_ALT			';'
# define DELIMS_CHARS				" \t"
# define QUOTES_CHAR		 		'\"'

typedef enum 				e_errors
{
	E_INVALID_COMMAND = 1,
	E_SEMANTIC_ERROR,
	E_UNKNOWN_INSTR,
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
	int						args;
}							t_counter;

typedef struct				s_file
{
	int						fd;
	char					*name;
	char					*data;
	char					*line;
}							t_file;

typedef struct				s_file_cor
{
	t_header				*header;
	char					*name;
	unsigned int			*bytecode;
}							t_file_cor;

typedef	struct				s_cmd_str
{
	char					*value;
	size_t					maxlen;
	size_t					len;
}							t_cmd_str;

typedef struct				s_label
{
	char					*name;
	size_t					len;
}							t_label;

typedef struct				s_token
{
	t_list					*labels;
	char					*instr;
	char					*args[MAX_ARGS_NUMBER - 1];
	// struct s_token			*next;
	// size_t					position;
}							t_token;

typedef struct				s_byte_code
{
	uint8_t   				instr_code;
	uint8_t					arg_code;
	uint8_t					reg;
	uint16_t				dir2;
	uint32_t				dir4;
	uint16_t				ind;
	size_t					size_bytes;
}							t_byte_code;

typedef struct				s_instr
{
	const char				*name;
	const uint8_t			op_code;
	uint8_t					args[MAX_ARGS_NUMBER - 1];
	t_byte_code				*(*bytecode_make)(t_list *tokens, t_counter *c);
}							t_instr;

// typedef struct				s_linker_label
// {
// 	t_list					*token;
// 	size_t					position;
// } 							t_linker_label;

// typedef struct				s_linker_ref
// {
// 	// t_token					*token;
// 	char					*reference;
// 	uint8_t					position;
// 	// struct s_linker_refs	*next;
// } 							t_linker_ref;

void				usage(void); // test version

/*
** counter
*/
t_counter			*counter_new(void);
void				counter_del(t_counter **c);
void				counter_clear(t_counter *c);

/*
** filename.*
*/
t_file 				*file_get(char *filename);
void				file_del(t_file **f);

/*
** flags
*/
uint8_t				flags_get(int *ac, char ***av, t_counter *c);

/*
** filename.cor
*/
t_file_cor			*file_cor_make(t_file *f, t_counter *c);		// test version
void			    file_cor_del(t_file_cor **fc);

int		         	file_get_line(t_file *f, t_counter *c, bool is_cmds);
size_t				get_currunet_column(t_counter *c);

/*
** header
*/
t_header			*header_get(t_file *f, t_counter *c);
void				header_del(t_header **h);

/*
** cmd
*/
void				cmd_str_set(t_file *f, t_header *h, t_counter *c);

/*
** label
*/
void    			append_label(t_list **label_head, t_label *label);
t_label				*get_solo_label(char *line, t_counter *counter);
t_label				*get_label(char *line, t_counter *counter);
/*
** token
*/
t_list				*tokens_make(t_file *f, t_counter *c); // test version
void				token_print(t_list *token);
/*
** Errors
*/
void    			lexical_errors(t_errors error, char *line, t_counter *c);
void				syntactic_errors(t_errors error, char *line, t_counter *c);
void    			semantic_errors(t_errors error, char *line, t_counter *c);

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

bool				is_whitespaces(const char c);

/* AUX */
ssize_t				get_invalid_symbols(char *line, size_t len);
void				ft_lstprint(t_list *elem);

t_token 			*live_compute(char *line, t_counter *counter);
t_token 			*ld_compute(char *line, t_counter *counter);
t_token 			*st_compute(char *line, t_counter *counter);
t_token 			*add_compute(char *line, t_counter *counter);
t_token 			*sub_compute(char *line, t_counter *counter);
t_token 			*and_compute(char *line, t_counter *counter);
t_token 			*or_compute(char *line, t_counter *counter);
t_token 			*xor_compute(char *line, t_counter *counter);
t_token 			*zjmp_compute(char *line, t_counter *counter);
t_token 			*ldi_compute(char *line, t_counter *counter);
t_token 			*sti_compute(char *line, t_counter *counter);
t_token 			*fork_compute(char *line, t_counter *counter);
t_token 			*lld_compute(char *line, t_counter *counter);
t_token 			*lldi_compute(char *line, t_counter *counter);
t_token 			*lfork_compute(char *line, t_counter *counter);
t_token 			*aff_compute(char *line, t_counter *counter);
#endif
