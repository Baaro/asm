/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 23:48:18 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/10 23:48:20 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmerge(t_list **list1, t_list *list2)
{
	t_list	*list_ptr;

	if (!list1 || !list2)
		return ;
	if (*list1)
	{
		list_ptr = *list1;
		while (list_ptr->next)
			list_ptr = list_ptr->next;
		list_ptr->next = list2;
	}
	else
		*list1 = list2;
}
