/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 23:45:23 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/10 23:45:25 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **list)
{
	t_list		*rev;
	t_list		*cur;
	t_list		*next;

	if (!list)
		return ;
	rev = NULL;
	cur = *list;
	while (cur)
	{
		next = cur->next;
		cur->next = rev;
		rev = cur;
		cur = next;
	}
	*list = rev;
}
