#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define VALID_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789%:,"
# define DELIMS	" \t"

size_t  ft_strcspn(const char *s1, const char *s2)
{
	const char *sc1;

	sc1 = s1;
	while (*sc1)
	{
		if (strchr(s2, *sc1))
			return (sc1 - s1);
		sc1++;
	}
	return (sc1 - s1);            /* terminating nulls match */
}

size_t	ft_strspn(const char *s1, const char *s2)
{
	const char *sc1;

	sc1 = s1;
	while (*sc1)
	{
		if (strchr(s2, *sc1) == NULL)
			return (sc1 - s1);
		sc1++;
	}
	return (sc1 - s1);            /* terminating nulls don't match */
}

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

	return (ft_strtok_r(s1, delimiters, &ssave));
}
char	*ft_strdup(const char *s1)
{
	char		*cs1;
	size_t		len;

	len = strlen(s1);
	if (!(cs1 = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	cs1 = strcpy(cs1, s1);
	return (cs1);
}

# define COMMENT_CHARS		 		"#;"

int     main(void)
{
	char *tmp;
	char *str = ft_strdup(".name zork\"");
	tmp = ft_strdup(ft_strtok(str, "\t \""));
	printf("%s\n", tmp);
	while ((tmp = ft_strdup(ft_strtok(NULL, "\t ,"))))
	{
		printf("%s\n", tmp);
	}
	return (0);
}

