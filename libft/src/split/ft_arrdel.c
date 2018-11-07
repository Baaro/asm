/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:18:47 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/10/20 21:18:48 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(char **arr)
{
	int		n;
	int		i;

	n = ft_arrlen(arr);
	i = -1;
	while (++i < n)
		free(arr[i]);
	free(arr);
}