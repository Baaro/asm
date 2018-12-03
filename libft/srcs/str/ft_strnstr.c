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

	if (!str || !to_f || *to_f == '\0')
		return ((char *)(str));
	i = -1;
	while (str[++i] && i < l)
	{
		j = 0;
		while (str[j + i] == to_f[j] && (l >= (ft_strlen(to_f))))
		{
			if (to_f[j + 1] == '\0')
				return ((char *)(str + i));
			j++;
		}
	}
	return (NULL);
}
