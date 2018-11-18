/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 17:22:09 by vsokolog          #+#    #+#             */
/*   Updated: 2017/12/04 13:43:46 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cntwords(char const *s, char c)
{
	int		word;
	int		i;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			word++;
		i++;
	}
	if (s[0] != c)
		word++;
	return (word);
}

static char		*putword(char const *s, char c, int *last_pos)
{
	char	*word;
	int		j;
	int		i;

	if (!(word = (char *)malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	j = 0;
	i = *last_pos;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = '\0';
	*last_pos = i;
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		last_pos;
	int		count;
	int		i;

	if (!s || !c)
		return (NULL);
	count = cntwords(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * count + 1)))
		return (NULL);
	i = 0;
	last_pos = 0;
	while (i < count)
	{
		arr[i] = putword(s, c, &last_pos);
		++i;
	}
	arr[i] = NULL;
	return (arr);
}
