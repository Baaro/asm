/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:24:06 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/07 22:24:08 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_len(int n)
{
	int		len;

	len = 2;
	len += (n < 0 ? 1 : 0);
	while (n /= 10)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	int		len;
	int		sig;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_get_len(n);
	sig = (n < 0 ? -1 : 1);
	res = (char*)malloc(sizeof(char) * len);
	if (!res)
		return (0);
	res[len-- - 1] = '\0';
	while (len--)
	{
		res[len] = (n % 10) * sig + '0';
		n /= 10;
	}
	if (sig == -1)
		res[0] = '-';
	return (res);
}
