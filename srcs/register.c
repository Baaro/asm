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
				printf("ERROR: %s\n", arg);
				exit(1);
			}
			copy_arg++;
		}
	}
	else
		return (false);
	return (true);
}

t_argument	reg_get(uint8_t instr_code, char *arg_str)
{
	t_argument	arg;

	ft_memset(&arg, 0, sizeof(arg));
	ft_memset(&arg.ref, 0, sizeof(t_reference));
	arg.code = REG_CODE;

}