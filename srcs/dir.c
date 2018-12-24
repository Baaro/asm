#include "asm.h"

bool				is_dir(char *arg_str) // add counter
{
	if (*arg_str == DIRECT_CHAR)
	{
		if (*(arg_str + 1) == LABEL_CHAR)
		{
			if (!is_label(arg_str + 2, ft_strlen(arg_str + 2)))
			{
				printf("wrong ref: %s\n", arg_str);
				exit(EXIT_FAILURE);
			}
		}
		else if (!is_valid_val(arg_str + 1))
		{
			printf("wrong val: %s\n", arg_str);
			exit(EXIT_FAILURE);
		}
		return (true);
	}
	return (false);
}

t_argument			*dir_get(uint8_t dir_size, char *arg_str)
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = DIR_CODE;
	if (*(arg_str + 1) == LABEL_CHAR)
	{
		arg->ref = ft_memalloc(sizeof(t_reference));
		arg->ref->len = ft_strlen(arg_str + 2);
		arg->ref->name = ft_strsub(arg_str, 2, arg->ref->len);
	}
	else
	{
		if (dir_size == USHORT)
			arg->dir16 = swap_uint16(ft_atoi64(arg_str + 1));
		else if (dir_size == UINT)
			arg->dir32 = swap_uint32(ft_atoi64(arg_str + 1));
	}
	arg->dir_size = dir_size;
	return (arg);
}
