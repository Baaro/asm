/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strredup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:05:18 by vsokolog          #+#    #+#             */
/*   Updated: 2018/05/15 16:05:19 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char		*ft_strredup(char *src)
{
	char	*dst;

	if (!src)
		return (NULL);
	if (!(dst = ft_memalloc(ft_strlen(src) + 1)))
		return (NULL);
	dst = ft_strcpy(dst, src);
	return (dst);
}
