/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cor_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:38:07 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/26 16:38:09 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	header_write(t_file_cor *fc)
{
	write(fc->fd, &fc->header->magic, sizeof(fc->header->magic));
	write(fc->fd, &fc->header->prog_name, PROG_NAME_LENGTH + 4);
	fc->size = swap_uint32(fc->size);
	write(fc->fd, &fc->size, sizeof(uint32_t));
	write(fc->fd, &fc->header->comment, COMMENT_LENGTH + 4);
}

void	op_write(int fd, t_b_token *b_token)
{
	if (b_token->op_code)
		write(fd, &b_token->op_code, sizeof(uint8_t));
}

void	args_write(int fd, t_b_token *b_token)
{
	ssize_t curr_arg;

	curr_arg = -1;
	if (b_token->args_code)
		write(fd, &b_token->args_code, sizeof(uint8_t));
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (b_token->args[curr_arg])
		{
			if (b_token->args[curr_arg]->code == REG_CODE)
				write(fd, &b_token->args[curr_arg]->val, sizeof(uint8_t));
			else if (b_token->args[curr_arg]->code == DIR_CODE)
			{
				if (b_token->args[curr_arg]->dir_size == USHORT)
					write(fd, &b_token->args[curr_arg]->val, sizeof(uint16_t));
				else if (b_token->args[curr_arg]->dir_size == UINT)
					write(fd, &b_token->args[curr_arg]->val, sizeof(uint32_t));
			}
			else if (b_token->args[curr_arg]->code == IND_CODE)
				write(fd, &b_token->args[curr_arg]->val, sizeof(uint16_t));
		}
	}
}

void	file_cor_write(t_file_cor *fc, uint8_t flags, t_counter *c)
{
	t_list *b_tokens;

	header_write(fc);
	b_tokens = fc->b_tokens;
	while (b_tokens)
	{
		op_write(fc->fd, (t_b_token *)b_tokens->content);
		args_write(fc->fd, (t_b_token *)b_tokens->content);
		b_tokens = b_tokens->next;
	}
	ft_printf("Writing output program to %s\n", fc->name);
}
