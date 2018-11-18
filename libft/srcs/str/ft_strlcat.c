/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:46:55 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/15 14:46:57 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t n_byte)
{
	char	*csrc;
	size_t	i;

	csrc = ft_strdup(src);
	csrc = ft_strcpy(csrc, src);
	if ((ft_strlen(dst)) >= n_byte)
		return (n_byte + ft_strlen(csrc));
	i = ft_strlen(dst);
	ft_strncat(dst + i, csrc, n_byte - i - 1);
	return (i + ft_strlen(csrc));
}
