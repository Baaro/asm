/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:22:15 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/14 17:22:16 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*cs1;
	size_t		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!(cs1 = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	cs1 = ft_strcpy(cs1, s1);
	return (cs1);
}
