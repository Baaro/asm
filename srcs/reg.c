#include "asm.h"

bool		is_reg(char *arg)
{
	char	*copy_arg;
	size_t	arg_len;

	copy_arg = arg;
	arg_len = ft_strlen(copy_arg);
	if (*copy_arg == 'r' && arg_len >= 1 && arg_len <= 3)
	{
		++copy_arg;
		while (*copy_arg)
		{
			if (!(ft_isdigit(*copy_arg)))
			{
				printf("error at reg: %s\n", arg);
				exit(1);
			}
			copy_arg++;
		}
	}
	else
		return (false);
	return (true);
}

t_argument			*reg_get(char *arg_str)
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = REG_CODE;
	arg->reg = ft_atoi64(arg_str + 1);
	if (arg->reg < 1 || arg->reg > 16)
	{
		printf("wrong reg: %s\n", arg_str);
		exit(1);
	}
    return (arg);

}