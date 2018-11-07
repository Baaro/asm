/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:16:47 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/04 17:16:49 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dos;
	unsigned char	*sor;

	dos = (unsigned char *)dst;
	sor = (unsigned char *)src;
	if (dos < sor)
		return (ft_memcpy(dos, sor, len));
	else
		while (len > 0)
		{
			dos[len - 1] = sor[len - 1];
			len--;
		}
	return (dos);
}
