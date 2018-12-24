#include "asm.h"

static void			args_valid_all_str(char *arg, t_counter *c)
{
	ssize_t	invalid_symbol;
	size_t	arglen;
	size_t	coma;

	arglen = ft_strlen(arg);
	if ((invalid_symbol = get_invalid_symbols(arg, arglen, ARGS_CHARS)) != -1)
	{
		c->column += arglen + (size_t)invalid_symbol - 1;
		lexical_errors(E_INVALID_SYMBOLS, arg, c);
	}
	coma = 0;
	while (*arg)
	{
		if (*arg == ',')
			coma++;
		if (coma > 2 || (*arg == ',' && *(arg + 1) == ','))
			lexical_errors(E_INVALID_SYMBOLS, arg, c);
		arg++;
	}
}

void				args_valid_begin_char(char args_begin)
{
	if (!(ft_strchr(VALID_CHARS, args_begin)))
	{
		printf("wrong separator %c\n", args_begin);
		exit(EXIT_FAILURE);
	}
}

void				args_valid_end_char(char args_begin)
{
	if (!(ft_strchr(VALID_CHARS, args_begin)))
	{
		printf("wrong separator %c\n", args_begin);
		exit(EXIT_FAILURE);
	}
}

void				args_get_strs(t_token *token, t_counter *c)
{
	ssize_t	args_counter;
	char	*args_str;

	if ((args_str = ft_strtrim(ft_strtok(NULL, "\0"))))
	{
		printf("args: %s\n", args_str);
		args_valid_all_str(args_str, c);
		args_valid_begin_char(*args_str);
		args_valid_end_char(args_str[ft_strlen(args_str) - 1]);
		args_counter = 0;
		token->args[args_counter] = ft_strtrim(ft_strtok(args_str, ","));
		while (++args_counter < MAX_ARGS_NUMBER)
			token->args[args_counter] = ft_strtrim(ft_strtok(NULL, ","));
		free(args_str);
	}
	else
	{
		printf("ERROR: NO ARGS!\n");
		exit(EXIT_FAILURE);
	}
}

static t_argument	*arg_get(t_b_token *bt, t_token *t, ssize_t curr_arg)
{
	t_argument	*arg;

	if (is_reg(t->args[curr_arg]))
		arg = reg_get(t->args[curr_arg]);
	else if (is_dir(t->args[curr_arg]))
		arg = dir_get(bt->op_template->dir_size, t->args[curr_arg]);
	else if (is_ind(t->args[curr_arg]))
		arg = ind_get(t->args[curr_arg]);
	else
	{
		printf("instr: %d\n", bt->op_template->code);
		printf("Wrong argument for [%s]!\n", bt->op_template->name);
		printf("t->args[curr_arg]: %s\n", t->args[curr_arg]);
		exit(EXIT_FAILURE);	
	}
	return (arg);
}

void				arg_valid(t_b_token *bt, ssize_t curr_arg) // add counter
{
	uint8_t arg_type;

	arg_type = 0;
	if (bt->args[curr_arg]->code == REG_CODE)
		arg_type = T_REG;
	else if (bt->args[curr_arg]->code == DIR_CODE)
		arg_type = T_DIR;
	else if (bt->args[curr_arg]->code == IND_CODE)
		arg_type = T_IND;
	if (bt->op_template->args[curr_arg] & arg_type)
		return ;
	else
	{
		printf("instr: %d\n", bt->op_template->code);
		printf("Wrong argument for [%s]!\n", bt->op_template->name);
		exit(EXIT_FAILURE);
	}
}

void				args_set(t_b_token *bt, t_token *t)
{
	uint8_t		shift;
	ssize_t		curr_arg;

	shift = 6;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER)
	{
		if (bt->op_template->args[curr_arg])
		{
			if (t->args[curr_arg])
			{
				bt->args[curr_arg] = arg_get(bt, t, curr_arg);
				arg_valid(bt, curr_arg);
				if (bt->op_template->codage)
				{
					bt->args_code |= bt->args[curr_arg]->code << shift;
					shift -= 2;
				}
			}
			else
			{
				printf("instr1: %d\n", bt->op_template->code);
				printf("Wrong argument for [%s]!\n",  bt->op_template->name);
				exit(EXIT_FAILURE);
			}
		}
		else if (t->args[curr_arg])
		{
			printf("instr: %d\n", bt->op_template->code);
			printf("Wrong argument for [%s]!\n",  bt->op_template->name);
			exit(EXIT_FAILURE);
		}
	}
}
