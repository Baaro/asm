/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:23:01 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/21 14:23:02 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*cs;

	if (s == NULL)
		return (NULL);
	if (!(cs = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strncpy(cs, s + start, len);
	cs[len] = '\0';
	return (cs);
}
