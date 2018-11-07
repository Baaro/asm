/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:17:24 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/07 20:17:26 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*res;
	unsigned char	*sor;

	res = (unsigned char *)dst;
	sor = (unsigned char *)src;
	while (n-- > 0)
	{
		if (*sor == (unsigned char)c)
		{
			*(res++) = *(sor++);
			return (res);
		}
		*(res++) = *(sor++);
	}
	return (0);
}
