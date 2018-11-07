/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:11:25 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/06 20:11:26 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	int		begin;
	int		end;
	int		len;

	if (!s)
		return (ft_strnew(0));
	begin = 0;
	while (s[begin] && ft_is_space(s[begin]))
		begin++;
	end = ft_strlen(s);
	while (begin < end && ft_is_space(s[end - 1]))
		end--;
	len = end - begin;
	if (len == 0)
		return (ft_strnew(0));
	else
		return (ft_strsub(s, begin, len));
}
