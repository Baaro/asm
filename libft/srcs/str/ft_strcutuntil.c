/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcutuntil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:24:57 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:24:58 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcutuntil(char *str, const char *until)
{
	size_t	position;

	if (str || until || *until)
	{
		if ((position = ft_strcspn(str, until)))
			return (ft_strsubcl(str, 0, position, 1));
	}
	return (NULL);
}
