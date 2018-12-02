#include "libft.h"

static char	*ft_strtok_r(char *s, const char *delimiters, char **lasts)
{
	char *sbegin;
	char *send;

	sbegin = s ? s : *lasts;
	sbegin += ft_strspn(sbegin, delimiters);
	if (*sbegin == '\0')
	{
		*lasts = "";
		return NULL;
	}
	send = sbegin + ft_strcspn(sbegin, delimiters);
	if (*send != '\0')
		*send++ = '\0';
	*lasts = send;
	return (sbegin);
}

char		*ft_strtok(char *s1, const char *delimiters)
{
	static char *ssave = "";

	return (strtok_r(s1, delimiters, &ssave));
}
