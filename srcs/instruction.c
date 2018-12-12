#include "asm.h"

// uint8_t         instruction_get_size()
// {

// }

// uint8_t         instruction_get_pos()
// {

// }

// uint8_t         instruction_get_code()
// {

// }

char			*instruction_get_str(char *fline, char *cur_line, t_counter *c)
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
