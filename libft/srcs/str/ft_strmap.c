/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:13:53 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/21 11:13:55 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*m;
	size_t	i;

	if (f == NULL || s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (!(m = ft_strnew(i)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		m[i] = f(s[i]);
		i++;
	}
	return (m);
}
