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

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*tmp;

	if (f == NULL || str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (!(tmp = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (str[++i])
		tmp[i] = f(i, str[i]);
	return (tmp);
}
