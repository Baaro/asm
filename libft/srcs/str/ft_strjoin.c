/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:56:07 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/23 11:56:08 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*concat;
	size_t		size_s1;
	size_t		size_s2;
	size_t		i;

	if (!s1 || !s2)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(concat = (char *)malloc(sizeof(char) * (size_s1 + size_s2 + 1))))
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		concat[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < size_s2)
	{
		concat[size_s1 + i] = s2[i];
		i++;
	}
	concat[size_s1 + i] = '\0';
	return (concat);
}
