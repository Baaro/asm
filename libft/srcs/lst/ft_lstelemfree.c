/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstelemfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:21:48 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:21:49 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstelemfree(void *content, size_t content_size)
{
	if (content)
	{
		ft_memset(content, 0, content_size);
		ft_memdel(&content);
	}
}
