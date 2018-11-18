/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:52:03 by vsokolog          #+#    #+#             */
/*   Updated: 2017/12/07 20:27:24 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*current;
	t_list	*nextlst;

	current = *alst;
	while (current)
	{
		nextlst = current->next;
		del(current->content, current->content_size);
		free(current);
		current = nextlst;
	}
	*alst = NULL;
}
