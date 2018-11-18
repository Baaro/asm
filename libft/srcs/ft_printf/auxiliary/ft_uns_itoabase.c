/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_itoabase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:52:53 by vsokolog          #+#    #+#             */
/*   Updated: 2018/03/19 14:52:54 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	length(uintmax_t value, uintmax_t base)
{
	int	i;

	i = 0;
	while (value >= base)
	{
		value /= base;
		i++;
	}
	return (i + 1);
}

char		*ft_uns_itoabase(uintmax_t value, uintmax_t base)
{
	char	*nbr;
	int		l;

	l = 0;
	l += length(value, base);
	if (!(nbr = (char*)(malloc(sizeof(nbr) * (l)))))
		return (NULL);
	nbr[l] = '\0';
	while (l--)
	{
		nbr[l] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value /= base;
	}
	return (nbr);
}
