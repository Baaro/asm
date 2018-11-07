/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:05:03 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/04/27 20:05:05 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wstrlen(unsigned *str, size_t fl, unsigned lim)
{
	size_t	len;
	size_t	l;

	len = 0;
	if (fl)
		while (*str != L'\0')
		{
			l = ft_wcharlen(*str++);
			if (len + l > lim)
				return (len);
			len += l;
		}
	else
	{
		while (*str != L'\0')
			len += ft_wcharlen(*str++);
	}
	return (len);
}
