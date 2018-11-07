/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:31:51 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/06 19:31:52 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (0);
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res = ft_strncpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
