/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 20:25:58 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/27 20:25:59 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_bonus(t_list *b_tkn, t_list *tkn, t_header *h, size_t s)
{
	t_list	*tmp_b_tkn;
	t_list	*tmp_tkn;

	tmp_b_tkn = b_tkn;
	tmp_tkn = tkn;
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %zu bytes\n", s);
	ft_printf("Name : \"%s\"\n", h->prog_name);
	ft_printf("Comment : \"%s\"\n\n", h->comment);
	while (tmp_tkn)
	{
		print_token((t_token *)tmp_tkn->content,\
		((t_b_token *)tmp_b_tkn->content)->pos,\
		((t_b_token *)tmp_b_tkn->content)->size);
		if (((t_token *)tmp_tkn->content)->op)
			print_b_token((t_b_token *)tmp_b_tkn->content);
		tmp_b_tkn = tmp_b_tkn->next;
		tmp_tkn = tmp_tkn->next;
	}
}
