/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:27:20 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/12/07 21:12:43 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*list;
	t_list		*next_link;

	if (!alst || !*alst)
		return ;
	list = *alst;
	while (list)
	{
		next_link = list->next;
		ft_lstdelone(&list, del);
		free(list);
		list = next_link;
	}
	*alst = NULL;
}
