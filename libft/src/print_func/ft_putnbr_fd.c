/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:31:42 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/17 17:43:08 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int a, int fd)
{
	if (a == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (a < 0)
	{
		ft_putchar_fd('-', fd);
		a = -a;
	}
	if (a >= 10)
	{
		ft_putnbr_fd(a / 10, fd);
		ft_putchar_fd(a % 10 + '0', fd);
	}
	else
		ft_putchar_fd(a + '0', fd);
}
