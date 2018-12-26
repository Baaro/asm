#include "libft.h"

int32_t		ft_atoi32(const char *str)
{
	size_t				i;
	int64_t		    	nbr;
	size_t				nums;
	bool				negative;

	i = 0;
	nbr = 0;
	nums = 0;
	negative = false;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == ' ') ||
		(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = true;
		i++;
	}
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		if (nbr > ((nbr * 10) + str[i] - '0') && !negative)
			return (-1);
		if (nbr > ((nbr * 10) + str[i] - '0') && negative)
			return (0);
		if ((nbr = (nbr * 10) + str[i] - '0'))
			nums++;
		i++;
	}
	if (negative == true)
		return (-nbr);
	return (nbr);
}
