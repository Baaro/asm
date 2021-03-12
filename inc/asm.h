/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 21:46:21 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/27 21:46:22 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/ft_printf.h"
# include <fcntl.h>
# include "op.h"
# define FLAG_A 1
# define OPS_CHARS "abcdefghijklmnopqrstuvwxyz"
# define VALID_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789%:-"
# define ARGS_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789%:-, \t"
# define NUM_INSTRUCTIONS 16
# define VALID 2
# define USHORT 2
# define UINT 4
# define COMMENT_CHARS ";#"
# define REG_CHAR 'r'
# define COMMENT_CHAR_ALT ';'
# define DELIMS_CHARS " \t"
# define QUOTES_CHAR '\"'

typedef enum	e_errors
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
	E_WRONG_ARGUMENT,
	E_UNKNOWN_REFERENCE,
	E_NO_ENDLINE,
	E_WRONG_LABEL_NAME,
}				t_errors;

typedef struct	s_counter
{
	size_t		column;
	size_t		row;
	size_t		begin_whitespaces;
	size_t		bytes;
	int			args;
}				t_counter;

typedef struct	s_file
{
	int			fd;
	char		*name;
	char		*data;
	char		*line;
}				t_file;

typedef struct	s_file_cor
{
	char		*name;
	uint32_t	modes;
	uint32_t	permissions;
	int			fd;
	t_header	*header;
	t_list		*tokens;
	t_list		*b_tokens;
	uint32_t	size;
}				t_file_cor;

typedef	struct	s_cmd_str
{
	char		*value;
	size_t		maxlen;
	size_t		len;
}				t_cmd_str;

typedef struct	s_label
{
	char		*name;
	size_t		len;
}				t_label;

typedef struct	s_reference
{
	char		*name;
	size_t		len;
}				t_reference;

typedef struct	s_argument
{
	uint8_t		code;
	uint8_t		dir_size;
	int32_t		val;
	t_reference	*ref;
}				t_argument;

typedef struct	s_token
{
	t_list		*labels;
	t_counter	*counter;
	char		*op;
	char		*args[MAX_ARGS_NUMBER];
}				t_token;

typedef struct	s_op_templ
{
	char		*name;
	uint8_t		code;
	uint8_t		args[MAX_ARGS_NUMBER];
	bool		codage;
	uint8_t		dir_size;
}				t_op_templ;

typedef struct	s_b_token
{
	uint8_t		op_code;
	bool		codage;
	uint8_t		args_code;
	uint32_t	pos;
	uint32_t	size;
	t_argument	*args[MAX_ARGS_NUMBER - 1];
	t_list		*labels;
	t_op_templ	*op_template;
}				t_b_token;

typedef struct	s_labels
{
	t_list		*all;
	t_list		*curr;
}				t_labels;

void			usage(void);

t_counter		*counter_new(void);
void			counter_del(t_counter **c);
void			counter_clear(t_counter *c);

t_file			*file_get(char *filename);
void			file_del(t_file **f);

uint8_t			flags_get(int *ac, char ***av, t_counter *c);

t_file_cor		*file_cor_make(t_file *f, t_counter *c);
void			file_cor_write(t_file_cor *fc, uint8_t flag);
void			file_cor_del(t_file_cor **fc);

int				file_get_line(t_file *f, t_counter *c, bool is_cmds);

t_header		*header_get(t_file *f, t_counter *c);
void			header_del(t_header **h);

void			cmd_str_set(t_file *f, t_header *h, t_counter *c);

bool			is_label(char *line, int32_t len);
void			label_append(t_list **curr_labs, t_list **all_labs, t_label *l);
t_label			*label_get_solo(char *line, t_counter *counter);
t_label			*label_get(char *line, t_counter *counter);
bool			label_exists(t_list *labels, char *label);

t_list			*tokens_make(t_file *f, t_counter *c);
void			tokens_del(t_list **tokens);
void			print_token(t_token *tkn, uint32_t pos, uint32_t size);

t_list			*b_tokens_make(t_list *tokens);
void			b_tokens_del(t_list **b_tokens);
void			b_token_print(t_list *b_token);
void			print_b_token(t_b_token *b_tkn);

char			*op_get_str(char *cur_line, t_counter *c);
uint32_t		op_get_pos(uint32_t pos, uint32_t size);
uint8_t			op_get_code(char *instr);
uint32_t		op_get_size(t_b_token *b_token);

void			args_get_strs(t_token *token, t_counter *c);
void			args_set(t_b_token *b_token, t_token *token);

bool			is_dir(char *arg);
t_argument		*dir_get(uint8_t dir_size, char *arg_str);

bool			is_ind(char *arg);
t_argument		*ind_get(char *arg_str);

bool			is_reg(char *arg);
t_argument		*reg_get(char *arg_str);

void			lexical_errors(t_errors error, t_counter *c);
void			syntactic_errors(t_errors error, char *line, t_counter *c);
void			semantic_errors(t_errors error, char *line, t_counter *c);
void			linker_errors(t_errors error, char *line);

void			print_bytes(int32_t val, bool four);
void			lists_to_null(t_list **first, t_list **second, t_list **third);
bool			is_whitespaces(const char c);
void			print_bonus(t_list *b_tkn, t_list *tkn, t_header *h, size_t s);
bool			is_comment(char c);
bool			is_endline(char c);
void			insert_addresses(t_list **b_tokens, uint32_t *size);
bool			is_valid_val(char *arg_str);
ssize_t			get_invalid_symbols(char *line, size_t len, char *valid_smbls);
void			ft_lstprint(t_list *elem);

static const t_op_templ	g_op_template_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live", 1, {T_DIR}, false, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, true, 4},
	{"st", 3, {T_REG, T_IND | T_REG}, true, 4},
	{"add", 4, {T_REG, T_REG, T_REG}, true, 4},
	{"sub", 5, {T_REG, T_REG, T_REG}, true, 4},
	{"and", 6, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, true, 4},
	{"or", 7, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, true, 4},
	{"xor", 8, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, true, 4},
	{"zjmp", 9, {T_DIR}, false, 2},
	{"ldi", 10, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, true, 2},
	{"sti", 11, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, true, 2},
	{"fork", 12, {T_DIR}, false, 2},
	{"lld", 13, {T_DIR | T_IND, T_REG}, true, 4},
	{"lldi", 14, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, true, 2},
	{"lfork", 15, {T_DIR}, false, 2},
	{"aff", 16, {T_REG}, true, 4},
	{0, 0, {0}, 0, 0}
};

#endif
