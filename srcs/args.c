#include "asm.h"

const t_instr 		g_instrs_tab[NUM_INSTRUCTIONS + 1];

static void			arg_valid_str(char *arg, t_counter *c)
{
	ssize_t	invalid_symbol;
	size_t	arglen;

	arglen = ft_strlen(arg);
	if ((invalid_symbol = get_invalid_symbols(arg, arglen, VALID_CHARS)) != -1)
	{
		c->column += (size_t)invalid_symbol - 1;
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
			arg_valid_str(token->args[i], c);
	}
}

static t_argument	*arg_get(uint8_t instr_code, char *arg_str)
{
	t_argument	*arg;

	if (is_reg(arg_str))
		arg = reg_get(instr_code, arg_str);
	else if (is_dir(arg_str))
		arg = dir_get(instr_code, arg_str);
	else if (is_ind(arg_str))
		arg = ind_get(instr_code, arg_str);
	return (arg);
}

void				arg_valid(uint8_t instr_code, uint8_t arg_code, ssize_t curr_arg) // add counter
{
	uint8_t arg_type;

	arg_type = 0;
	if (arg_code == REG_CODE)
		arg_type = T_REG;
	else if (arg_code == DIR_CODE)
		arg_type = T_DIR;
	else if (arg_code == IND_CODE)
		arg_type = T_IND;
	if (g_instrs_tab[instr_code - 1].args[curr_arg] & arg_type)
		return ;
	else
	{
		printf("instr: %d\n", instr_code);
		printf("Wrong argument for [%s]!\n", g_instrs_tab[instr_code - 1].name);
		exit(1);
	}
}

void				args_set(t_b_token *bc, t_token *t)
{
	uint8_t		shift;
	ssize_t		curr_arg;

	shift = 6;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (t->args[curr_arg])
		{
			bc->args[curr_arg] = arg_get(bc->instr_code, t->args[curr_arg]);
			arg_valid(bc->instr_code, bc->args[curr_arg]->code, curr_arg);
			if (g_instrs_tab[bc->instr_code - 1].args_types)
			{
				bc->args_code |= bc->args[curr_arg]->code << shift;
				shift -= 2;
			}
		}
		else if (g_instrs_tab[bc->instr_code - 1].args[curr_arg])
		{
			printf("instr: %d\n", g_instrs_tab[bc->instr_code - 1].instr_code);
			printf("Wrong argument for [%s]!\n", g_instrs_tab[bc->instr_code - 1].name);
			exit(1);
		}
	}
}
