/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:17:54 by vsokolog          #+#    #+#             */
/*   Updated: 2017/11/21 13:17:55 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		m[i] = f(i, s[i]);
		i++;
	}
	return (m);
}
