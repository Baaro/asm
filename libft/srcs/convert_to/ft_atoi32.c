/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:15:47 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:15:48 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t		ft_atoi32(const char *str)
{
	size_t				i;
	int64_t				nbr;
	bool				negative;

	i = 0;
	nbr = 0;
	negative = false;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == ' ') ||
		(str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		negative = true;
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
