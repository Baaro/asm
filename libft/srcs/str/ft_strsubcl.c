#include "libft.h"

char	*ft_strsubcl(char *s, unsigned int start, size_t len, bool clear)
{
	char	*cs;

	if (s == NULL)
		return (NULL);
	if (!(cs = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	strncpy(cs, s + start, len);
	cs[len] = '\0';
	if (clear)
		ft_strdel(&s);
	return (cs);
}
