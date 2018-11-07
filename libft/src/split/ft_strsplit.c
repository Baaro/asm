/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:27:54 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/06 21:27:56 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(char const *s, char c)
{
	int			words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		else
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

static char		*make_word(char const *s, char *word, int *i, char c)
{
	int			len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	word = ft_strsub(s - len, 0, len);
	*i += len;
	return (word);
}

static void		add_word(char **res, char *word, int k)
{
	int			len;

	len = ft_strlen(word);
	*(res + k) = (char*)malloc(sizeof(*(res)) * (len + 1));
	if (!*(res + k))
		return ;
	*(res + k) = ft_strcpy(*(res + k), word);
	free(word);
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			k;
	int			len;
	char		*word;
	char		**res;

	if (!s)
		return (0);
	len = word_count(s, c) + 1;
	res = (char **)malloc(sizeof(char*) * len);
	if (!res)
		return (0);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		word = make_word(s + i, word, &i, c);
		add_word(res, word, k);
		k++;
	}
	*(res + len - 1) = 0;
	return (res);
}
