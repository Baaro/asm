#include "asm.h"

const t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												4},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									4},
	{"st",		3,	{T_REG, T_IND | T_REG},									4},
	{"add",		4,	{T_REG, T_REG, T_REG},									4},
	{"sub",		5,	{T_REG, T_REG, T_REG},									4},	
	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"zjmp",	9,	{T_DIR},												2},
	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2},
	{"fork",	12,	{T_DIR},												2},
	{"lld",		13,	{T_DIR | T_IND, T_REG},									4},
	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"lfork",	15,	{T_DIR},												2},
	{"aff",		16,	{T_REG},												4},
	{0, 		0,	{0}}
};

uint8_t				instruction_get_code(char *instr)
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

size_t				instruction_get_pos(t_bytecode *b_prevtoken)
{
	return (b_prevtoken ? b_prevtoken->pos + b_prevtoken->size : 0);
}

// size_t				instruction_get_size(t_bytecode *b_token)
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
