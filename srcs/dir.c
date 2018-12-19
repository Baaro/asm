#include "asm.h"

const t_instr	g_instrs_tab[NUM_INSTRUCTIONS + 1];

bool				is_dir(char *arg_str) // add counter
{
	if (*arg_str == DIRECT_CHAR)
	{
		if (*(arg_str + 1) == LABEL_CHAR)
		{
			if (!is_label(arg_str + 2))
			{
				printf("wrong ref: %s\n", arg_str);
				exit(1);
			}
		}
		else if (!is_valid_val(arg_str + 1))
		{
			printf("wrong val: %s\n", arg_str);
			exit(1);
		}
		return (true);
	}
	return (false);
}

t_argument			*dir_get(uint8_t instr_code, char *arg_str) // add counter
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = DIR_CODE;
	if (*(arg_str + 1) == LABEL_CHAR)
	{
		arg->ref.len = ft_strlen(arg_str + 2);
		arg->ref.name = ft_strsub(arg_str, 2, arg->ref.len);
	}
	else
	{
		if (g_instrs_tab[instr_code - 1].dir_size == USHORT)
			arg->dir16 = swap_uint16(ft_atoi64(arg_str + 1));
		else if (g_instrs_tab[instr_code - 1].dir_size == UINT)
			arg->dir32 = swap_uint32(ft_atoi64(arg_str + 1));
	}
	arg->dir_size = g_instrs_tab[instr_code - 1].dir_size;
	return (arg);
}
