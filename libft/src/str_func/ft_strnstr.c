/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:43:46 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/04 16:43:49 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	int		i;
	int		j;
	size_t	tmp;

	i = 0;
	if (*lit == '\0')
		return ((char*)big);
	while (big[i] && len > 0)
	{
		j = 0;
		tmp = len;
		while (lit[j] == big[i + j] && tmp > 0)
		{
			if (lit[j + 1] == '\0')
				return ((char*)big + i);
			j++;
			tmp--;
		}
		i++;
		len--;
	}
	return (0);
}
