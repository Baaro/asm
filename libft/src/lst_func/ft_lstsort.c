/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:53:14 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/11/11 12:53:16 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_list_swap(t_list **current)
{
	t_list	*tmp;

	tmp = (*current)->next->next;
	(*current)->next->next = (*current);
	(*current)->next = tmp;
}

void			ft_lstsort(t_list **lst, int (*cmp)())
{
	t_list	*current;
	t_list	*last;

	current = *lst;
	if (!*lst)
		return ;
	last = (t_list*)malloc(sizeof(t_list));
	while (current->next)
	{
		if ((*cmp)(current->content, current->next->content) > 0)
		{
			if (current != *lst)
				last->next = current->next;
			else
				*lst = current->next;
			ft_list_swap(&current);
			current = *lst;
		}
		else
		{
			last = current;
			current = current->next ? current->next : current;
		}
	}
	free(last);
}
