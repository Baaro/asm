/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hesh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 19:27:02 by vsokolog          #+#    #+#             */
/*   Updated: 2018/05/02 19:27:04 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hesh(char **flg, t_arg arg)
{
	if (arg.type == 'x' || arg.type == 'p')
	{
		*flg = ft_strnew(2);
		(*flg)[0] = '0';
		(*flg)[1] = 'x';
	}
	else if (arg.type == 'X')
	{
		*flg = ft_strnew(2);
		(*flg)[0] = '0';
		(*flg)[1] = 'X';
	}
	else if (arg.type == 'o' || arg.type == 'O')
	{
		*flg = ft_strnew(1);
		(*flg)[0] = '0';
	}
}
