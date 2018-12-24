#include "asm.h"

const static t_op_template	g_op_template_tab[NUM_INSTRUCTIONS + 1];

char			*op_get_str(char *fline, char *cur_line, t_counter *c)
{
	ssize_t		invalid_symbol;
	char		*op_name;
	char		*tmp;
	size_t		op_len;

	op_name = ft_strtrim(ft_strtok(cur_line, DELIMS_CHARS));
	if ((ft_strchr(op_name, '%')))
	{
		op_name = ft_strjoin(ft_strtok(op_name, "%"), " %");
		op_name = ft_strjoincl(op_name, ft_strtok(NULL, "\0"), 0);
		op_name = ft_strtrim(ft_strtok(op_name, DELIMS_CHARS));
	}
	op_len = ft_strlen(op_name);
	if ((invalid_symbol = get_invalid_symbols(op_name, op_len, OPS_CHARS)) != -1)
	{
		c->column += op_len + (size_t)invalid_symbol;
		lexical_errors(E_INVALID_SYMBOLS, fline, c);
	}
	return (op_name);
}

uint8_t			op_get_code(char *op)
{
	uint8_t	op_code;
	uint8_t	op_len;
	ssize_t curr_instr;

	op_code = 0;
	curr_instr = -1;
	while (++curr_instr < NUM_INSTRUCTIONS)
	{
		op_len = ft_strlen(g_op_template_tab[curr_instr].name);
		if (ft_strnequ(g_op_template_tab[curr_instr].name, op, op_len))
			op_code = g_op_template_tab[curr_instr].code;
	}
	if (op_code == 0)
		semantic_errors(E_UNKNOWN_INSTR, op, NULL);
	return (op_code);
}

uint32_t		op_get_pos(uint32_t pos, uint32_t size)
{
	return (size || pos ? pos + size : 0);
}

uint32_t		op_get_size(t_b_token *b_token)
{
	uint32_t	size;
	ssize_t		curr_arg;

	if (!b_token->op_code)
		return (0);
	size = 1;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (!b_token->args[curr_arg])
			break ;
		if (b_token->args[curr_arg]->code == REG_CODE)
			size += 1;
		else if (b_token->args[curr_arg]->code == DIR_CODE)
			size += b_token->args[curr_arg]->dir_size;
		else if (b_token->args[curr_arg]->code == IND_CODE)
			size += 2;
	}
	if (curr_arg >= 1 && b_token->codage)
		size += 1;
	return (size);
}

