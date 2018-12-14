#include "asm.h"

bool				is_dir(char *arg)
{
	return (*arg == DIRECT_CHAR);
}

t_argument			dir_get(uint8_t instr_code, char *arg_str)
{
	t_argument	arg;

	ft_memset(&arg, 0, sizeof(arg));
	ft_memset(&arg.ref, 0, sizeof(t_reference));
	arg.code = DIR_CODE;
	if (*(arg_str + 1) == LABEL_CHAR && is_label(arg_str + 2))
	{
		arg.ref.len = ft_strlen(arg_str + 2);
		arg.ref.name = ft_strsub(arg_str, 2, arg.ref.len);
	}
	else
	{
		arg.value = (size_t)ft_atoi(arg_str);
		if (ft_strlen(ft_itoa((int)arg.value)) != ft_strlen(arg_str))
		{
			printf("WRONG_SYMB: %s\n", arg_str);
			exit(1);
		}
	}
}
