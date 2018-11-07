/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:38:43 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/06 19:38:44 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res = ft_strcpy(res, s1);
	res = ft_strcat(res, s2);
	res[len] = '\0';
	return (res);
}
