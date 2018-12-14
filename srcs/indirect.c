#include "asm.h"

bool				is_ind(char *arg)
{
	if (!ft_strchr(LABEL_CHARS, *arg))
		lexical_errors(E_INVALID_SYMBOLS, arg, NULL);
	return (true);
}


t_argument			ind_get(uint8_t instr_code, char *arg_str)
{
	t_argument	arg;

	ft_memset(&arg, 0, sizeof(arg));
	ft_memset(&arg.ref, 0, sizeof(t_reference));
	arg.code = IND_CODE;

}
