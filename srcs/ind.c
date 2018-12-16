#include "asm.h"

/*
** possible values
** :label
** -123
** 123
*/

bool				is_ind(char *arg_str) // add counter
{
	if (*arg_str == LABEL_CHAR)
	{
		if (!is_label(arg_str + 1))
		{
			printf("wrong ref: %s\n", arg_str);
			exit(1);
		}
		return (true);
	}
	else if (*arg_str == '-' || ft_isdigit(*arg_str))
	{
		if (!is_valid_val(arg_str))
		{
			printf("wrong val: %s\n", arg_str);
			exit(1);
		}
		return (true);
	}
	else if (ft_isalpha(*arg_str))
	{
		printf("wrong val: %s\n", arg_str);
		exit(1);
	}
	return (false);
}

t_argument			*ind_get(uint8_t instr_code, char *arg_str) // add counter
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = IND_CODE;
	if (*arg_str == LABEL_CHAR)
	{
		arg->ref.len = ft_strlen(arg_str + 1);
		arg->ref.name = ft_strsub(arg_str, 1, arg->ref.len);
	}
	else
		arg->val16 = ft_atoi64(arg_str);
    return (arg);
}
