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

int     main(void)
{
	char	*str;
	char	*instr;
	size_t	column;

	column = 0;
	str = malloc(sizeof(char) * strlen("	sti	r1, %:live, %1") + 1);
	str = strcpy(str, "	sti	r1, %:live, %1");
	// printf("1. [%zu]: str: %s\n", column, str + column);

	// column = ft_strspn(str, DELIMS);
	// printf("2. [%zu]: str: %s\n", column, str + column);

	// column += ft_strcspn(str + column, DELIMS);
	// printf("3. [%zu]: str: %s\n", column, str + column);

	instr = ft_strtok(str, DELIMS);
	printf("instruction: %s\n", instr);
	instr = ft_strtok(NULL, DELIMS);
	printf("instruction: %s\n", instr);
	return (0);
}
