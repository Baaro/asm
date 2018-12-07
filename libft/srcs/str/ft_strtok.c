#include "libft.h"

char		*ft_strtok(char *s, const char *delimiters)
{
	static char *s_save = "";

	return (ft_strtok_r(s, delimiters, &s_save));
}
