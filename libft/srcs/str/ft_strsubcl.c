/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubcl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:25:39 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:25:40 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubcl(char *s, uint32_t start, size_t len, bool clr)
{
	char	*cs;

	if (s == NULL)
		return (NULL);
	if (!(cs = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	strncpy(cs, s + start, len);
	cs[len] = '\0';
	if (clr)
		ft_strdel(&s);
	return (cs);
}
