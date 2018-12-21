#include "asm.h"

static void			arg_valid_str(char *arg, t_counter *c)
{
	ssize_t	invalid_symbol;
	size_t	arglen;

	arglen = ft_strlen(arg);
	if ((invalid_symbol = get_invalid_symbols(arg, arglen, VALID_CHARS)) != -1)
	{
		c->column += arglen + (size_t)invalid_symbol - 1;
		lexical_errors(E_INVALID_SYMBOLS, arg, c);
	}
}

void				args_get_strs(t_token *token, t_counter *c)
{
	ssize_t	i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
	{
		token->args[i] = ft_strtrim(ft_strtok(NULL, ","));
		if (token->args[i])
		{
			arg_valid_str(token->args[i], c);
		}
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
		exit(1);	
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
		exit(1);
	}
}

void				args_set(t_b_token *bt, t_token *t)
{
	uint8_t		shift;
	ssize_t		curr_arg;

	shift = 6;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
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
		else if (bt->op_template->args[curr_arg])
		{
			printf("instr: %d\n", bt->op_template->code);
			printf("Wrong argument for [%s]!\n",  bt->op_template->name);
			exit(1);
		}
	}
}
