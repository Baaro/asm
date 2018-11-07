/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:54:16 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/04 17:54:18 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*st1;
	const unsigned char		*st2;

	if (s1 == s2 || n == 0)
		return (0);
	st1 = (const unsigned char*)s1;
	st2 = (const unsigned char*)s2;
	while (n > 0)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
		n--;
	}
	return (0);
}
