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

void		header_write(t_file_cor *fc)
{
	write(fc->fd, &fc->header->magic, sizeof(fc->header->magic));
	write(fc->fd, &fc->header->prog_name, PROG_NAME_LENGTH + 4);
	fc->size = swap_uint32(fc->size);
	write(fc->fd, &fc->size, sizeof(uint32_t));
	write(fc->fd, &fc->header->comment, COMMENT_LENGTH + 4);
}

void		op_write(int fd, t_b_token *b_token)
{
	if (b_token->op_code)
		write(fd, &b_token->op_code, sizeof(uint8_t));
}

uint32_t	swap_bytes(t_argument *arg)
{
	uint32_t	val;

	val = arg->val;
	if (arg->code == IND_CODE)
		val = swap_uint16(arg->val);
	else if (arg->code == DIR_CODE)
	{
		if (arg->dir_size == USHORT)
			val = swap_uint16(arg->val);
		else if (arg->dir_size == UINT)
			val = swap_uint32(arg->val);
	}
	return (val);
}

void		args_write(int fd, t_b_token *b_token)
{
	uint32_t	val;
	ssize_t		curr_arg;

	val = 0;
	curr_arg = -1;
	if (b_token->args_code)
		write(fd, &b_token->args_code, sizeof(uint8_t));
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (b_token->args[curr_arg])
		{
			val = swap_bytes(b_token->args[curr_arg]);
			if (b_token->args[curr_arg]->code == REG_CODE)
				write(fd, &val, sizeof(uint8_t));
			else if (b_token->args[curr_arg]->code == DIR_CODE)
			{
				if (b_token->args[curr_arg]->dir_size == USHORT)
					write(fd, &val, sizeof(uint16_t));
				else if (b_token->args[curr_arg]->dir_size == UINT)
					write(fd, &val, sizeof(uint32_t));
			}
			else if (b_token->args[curr_arg]->code == IND_CODE)
				write(fd, &val, sizeof(uint16_t));
		}
	}
}

void		file_cor_write(t_file_cor *fc, uint8_t flag)
{
	t_list *b_tokens;

	if (flag & FLAG_A)
		print_bonus(fc->b_tokens, fc->tokens, fc->header, fc->size);
	else
	{
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
}
