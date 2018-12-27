/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:26:03 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:26:04 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *s, const char *delimiters, char **lasts)
{
	char *s_begin;
	char *s_end;

	s_begin = s ? s : *lasts;
	s_begin += ft_strspn(s_begin, delimiters);
	if (*s_begin == '\0')
	{
		*lasts = "";
		return (NULL);
	}
	s_end = s_begin + ft_strcspn(s_begin, delimiters);
	if (*s_end != '\0')
		*s_end++ = '\0';
	*lasts = s_end;
	return (s_begin);
}
