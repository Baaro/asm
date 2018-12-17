#include "asm.h"

const t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1];

uint8_t			instr_get_code(char *instr)
{
	uint8_t	instr_code;
	ssize_t curr_instr;

	instr_code = 0;
	curr_instr = -1;
	while (++curr_instr < NUM_INSTRUCTIONS)
	{
		if (ft_strnequ(g_instrs_tab[curr_instr].name, instr, ft_strlen(instr)))
			instr_code = g_instrs_tab[curr_instr].instr_code;
	}
	if (instr_code == 0)
		semantic_errors(E_UNKNOWN_INSTR, instr, NULL);
	return (instr_code);
}

size_t			instr_get_pos(t_bytecode *b_prevtoken)
{
	return (b_prevtoken ? b_prevtoken->pos + b_prevtoken->size : 0);
}

size_t		instr_get_size(t_bytecode *b_token)
{
	size_t	size;
	ssize_t	curr_arg;

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
	return (curr_arg > 1 ? size + 1 : size);
}

char			*instr_get_str(char *fline, char *cur_line, t_counter *c)
{
	ssize_t		invalid_symbol;
	char		*instr;

	instr = ft_strtrim(ft_strtok(cur_line, DELIMS_CHARS));
	if ((invalid_symbol = get_invalid_symbols(instr, ft_strlen(instr), INSTR_CHARS)) != -1)
	{
		c->column += ft_strlen(instr) + (size_t)invalid_symbol;
		lexical_errors(E_INVALID_SYMBOLS, fline, c);
	}
	return (instr);
}
