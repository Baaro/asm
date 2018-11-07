/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 18:56:42 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/05 18:56:44 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void	*res;

	res = malloc(size + 1);
	if (!res)
		return (0);
	else
	{
		ft_memset(res, '\0', size + 1);
		return (res);
	}
}
