/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:19:23 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/11 13:19:25 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_arrlen(char **str)
{
	int		len;

	len = 0;
	while (*str != 0)
	{
		str++;
		len++;
	}
	return (len);
}

char			**ft_strsort(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	if (!str)
		return (0);
	j = ft_arrlen(str);
	while (j > 0)
	{
		i = 0;
		while (i < j - 1)
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				tmp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = tmp;
			}
			i++;
		}
		j--;
	}
	return (str);
}
