/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:35:28 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/07 21:35:31 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int					i;
	int					sig;
	unsigned long int	res;

	i = 0;
	res = 0;
	sig = 1;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (((res == 922337203685477580 && (str[i] - '0') > 7) ||
			res > 922337203685477580) && sig == 1)
			return (-1);
		else if (((res == 922337203685477580 && (str[i] - '0') > 8) ||
			res > 922337203685477580) && sig == -1)
			return (0);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(res * sig));
}
