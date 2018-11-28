/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strretrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:01:03 by vsokolog          #+#    #+#             */
/*   Updated: 2018/11/28 11:01:04 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strretrim(char *s)
{
	char	*cs;
	size_t	end;
	size_t	begin;
	size_t	len;

	if (s == NULL)
		return (NULL);
	end = ft_strlen(s) - 1;
	begin = 0;
	len = 0;
	while ((s[end] == '\n' || s[end] == '\t' || s[end] == ' ') && (end > 0))
		end--;
	while (s[begin] == '\n' || s[begin] == '\t' || s[begin] == ' ')
		begin++;
	len = end - begin + 1;
	if (end == 0)
		cs = ft_strdup("");
	else if (!(cs = ft_strsub(s, begin, len)))
		return (NULL);
	free(s);
	return (cs);
}
