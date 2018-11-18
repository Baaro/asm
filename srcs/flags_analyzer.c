#include "info.h"

static bool is_flag(const char *flag)
{
	return (*flag == '-' && *(flag + 2) == '\0');
}

static bool is_flag_a(const char *flag)
{
	return (*flag == '-' && *(flag + 1) == 'a' && *(flag + 2) == '\0');
}

static bool is_flag_m(const char *flag)
{
	return (*flag == '-' && *(flag + 1) == 'm' && *(flag + 2) == '\0');
}

uint8_t     flags_analyze(int *ac, char ***av)
{
	uint8_t	flags;
	int		args_counter;

	flags = 0;
	args_counter = 0;
	while (++args_counter < *ac && is_flag((*av)[args_counter]))
	{
		if (is_flag_a((*av)[args_counter]))
			flags |= FLAG_A;
		else if (is_flag_m((*av)[args_counter]))
			flags |= FLAG_M;
	}
	*ac -= args_counter;
	*av += args_counter;
	return (flags);
}
