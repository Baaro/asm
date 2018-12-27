/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:21:06 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:21:07 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *elem)
{
	t_list *copy;

	if (!elem)
		return (NULL);
	if (!(copy = ft_lstnew(elem->content, elem->content_size)))
		return (NULL);
	return (copy);
}
