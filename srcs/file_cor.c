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

void    			file_cor_del(t_file_cor **fc)
{
	ft_memdel((void**)&(*fc)->header);
	tokens_del(&(*fc)->tokens);
	b_tokens_del(&(*fc)->b_tokens);
	free((*fc)->name);
	free(*fc);
}

void				file_cor_write(t_file_cor *fc, uint8_t flags, t_counter *c)
{
	ssize_t curr_arg;

	write(fc->fd, &fc->header->magic, sizeof(fc->header->magic));
	write(fc->fd, &fc->header->prog_name, PROG_NAME_LENGTH + 4);
	fc->size = swap_uint32(fc->size);
	write(fc->fd, &fc->size, sizeof(uint32_t));
	write(fc->fd, &fc->header->comment, COMMENT_LENGTH + 4);
	t_list *b_tokens = fc->b_tokens;
	while (b_tokens)
	{
		if (((t_b_token *)b_tokens->content)->op_code)
			write(fc->fd, &((t_b_token *)b_tokens->content)->op_code, sizeof(uint8_t));
		if (((t_b_token *)b_tokens->content)->args_code)
			write(fc->fd, &((t_b_token *)b_tokens->content)->args_code, sizeof(uint8_t));
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)b_tokens->content)->args[curr_arg])
			{
				if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == REG_CODE)
					write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->reg, sizeof(uint8_t));
				else if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == DIR_CODE)
				{
					if (((t_b_token *)b_tokens->content)->args[curr_arg]->dir_size == USHORT)
						write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->dir16, sizeof(uint16_t));
					else if (((t_b_token *)b_tokens->content)->args[curr_arg]->dir_size == UINT)
						write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->dir32, sizeof(uint32_t));
				}
				else if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == IND_CODE)
					write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->ind, sizeof(uint16_t));
			}
		}
		b_tokens = b_tokens->next;
	}
}

char				*file_cor_get_name(char *f_name)
{
	char	*slash;
	char	*dot;
	char	*fc_name;

	slash = ft_strrchr(f_name, '/');
	dot = ft_strrchr(slash, '.');
	fc_name = ft_strsub(slash + 1, 0, dot - slash);
	fc_name = ft_strjoincl(fc_name, "cor", 0);
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

	// ft_lstiter(fc->tokens, token_print);
	// ft_lstiter(fc->b_tokens, b_token_print);
	return (fc);
}
