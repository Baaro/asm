/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:02 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:03 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_file_cor	*file_cor_new(void)
{
	return (ft_memalloc(sizeof(t_file_cor)));
}

void				file_cor_del(t_file_cor **fc)
{
	ft_memdel((void**)&(*fc)->header);
	tokens_del(&(*fc)->tokens);
	b_tokens_del(&(*fc)->b_tokens);
	free((*fc)->name);
	free(*fc);
}

char				*file_cor_get_name(char *f_name)
{
	char	*slash;
	char	*dot;
	char	*fc_name;

	slash = NULL;
	dot = NULL;
	fc_name = NULL;
	if ((slash = ft_strrchr(f_name, '/')))
	{
		if ((dot = ft_strrchr(slash, '.')))
			fc_name = ft_strsub(slash + 1, 0, dot - slash - 1);
		else
			fc_name = ft_strsub(slash + 1, 0, slash - f_name);
	}
	else if ((dot = ft_strrchr(f_name, '.')))
		fc_name = ft_strsub(f_name, 0, dot - f_name);
	fc_name = ft_strjoincl(fc_name, ".cor", 0);
	return (fc_name);
}

t_file_cor			*file_cor_make(t_file *f, t_counter *c)
{
	t_file_cor	*fc;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	fc->tokens = tokens_make(f, c);
	fc->b_tokens = b_tokens_make(fc->tokens);
	insert_addresses(&fc->b_tokens, &fc->size);
	fc->name = file_cor_get_name(f->name);
	fc->modes = O_RDWR | O_TRUNC | O_CREAT;
	fc->permissions = S_IWUSR | S_IRUSR;
	fc->fd = open(fc->name, fc->modes, fc->permissions);
	return (fc);
}
