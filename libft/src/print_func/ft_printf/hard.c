/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:03:42 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/04/14 20:03:44 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_pointer(t_pr *pr)
{
	void	*point;

	point = va_arg(pr->list, void *);
	pr->fl |= FL_POINTER;
	pr->fl |= FL_HASH;
	pf_itoa_un(pr, (uintmax_t)point, 16);
}

void	ft_realloc(t_pr *pr)
{
	char	*new;
	size_t	i;

	new = (char*)ft_memalloc(sizeof(char) * (pr->size * 2 + 1));
	i = -1;
	while (++i < pr->buff_len)
		new[i] = pr->buff[i];
	new[pr->buff_len] = '\0';
	free(pr->buff);
	pr->buff = new;
	pr->size *= 2;
}

void	ft_erase_flags(t_pr *pr)
{
	pr->fl = 0;
	pr->width = 0;
	pr->precision = 0;
}

void	ft_without_type(t_pr *pr)
{
	if ((pr->padding = pr->width - 1) > 0)
	{
		ft_padding(pr, 0);
		ft_buffer_char(pr, *pr->format);
		ft_padding(pr, 1);
	}
	else
		ft_buffer_char(pr, pr->c);
}

void	ft_padding(t_pr *pr, int n)
{
	if (!pr->padding)
		return ;
	pr->c = 32 | (pr->fl & FL_ZERO);
	if (n == (pr->fl & FL_MINUS))
		while (pr->padding--)
			ft_buffer(pr, &pr->c, 1);
}
