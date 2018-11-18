/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupcl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:32:53 by vsokolog          #+#    #+#             */
/*   Updated: 2018/09/05 13:32:54 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdupcl(char *to_del, const char *to_copy)
{
	char *tmp;

	if (!to_del || !to_copy)
		return (NULL);
	tmp = ft_strdup(to_copy);
	ft_strdel(&to_del);
	return (tmp);
}
