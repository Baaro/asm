/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:27:36 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/16 15:27:37 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_f, size_t l)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (to_f[i] == '\0')
		return ((char *)(str));
	while (str[i] && l)
	{
		while (str[i + j] == to_f[j] && (l >= (ft_strlen(to_f))))
		{
			if (to_f[j + 1] == '\0')
				return ((char *)(str + i));
			j++;
		}
		i++;
		l--;
		j = 0;
	}
	return (NULL);
}
