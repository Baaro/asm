/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 13:58:49 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/09/30 13:58:54 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *begin_list)
{
	t_list		*list;
	int			count;

	count = 0;
	list = begin_list;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}
