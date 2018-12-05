#include "libft.h"

char		*ft_strcutuntil(char *str, const char *until)
{
	size_t	position;

	if (!str || !until || !(*until))
		return (str);
	if ((position = ft_strcspn(str, until)))
		return (ft_strsubcl(str, 0, position, 1));
	return (str);
}
