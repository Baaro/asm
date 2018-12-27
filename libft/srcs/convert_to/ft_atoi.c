/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:19:23 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/04 13:13:55 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					i;
	int64_t				nbr;
	int					negative;

	i = 0;
	nbr = 0;
	negative = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == ' ') ||
		(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		negative = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		if (nbr > ((nbr * 10) + str[i] - '0') && !negative)
			return (-1);
		if (nbr > ((nbr * 10) + str[i] - '0') && negative)
			return (0);
		nbr = (nbr * 10) + str[i] - '0';
		i++;
	}
	return (negative ? -nbr : nbr);
}
