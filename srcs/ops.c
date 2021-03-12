/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:36 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:38 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static const t_op_templ	g_op_template_tab[NUM_INSTRUCTIONS + 1];

static void		op_exists(char *op)
{
	ssize_t	cur_op;

	cur_op = -1;
	while (++cur_op < NUM_INSTRUCTIONS)
		if (ft_strequ(op, g_op_template_tab[cur_op].name))
			return ;
	ft_printf(RED"ERROR: "RESET"Unknown operation: [%s]!\n", op);
	exit(EXIT_FAILURE);
}

char			*op_get_str(char *cur_line, t_counter *c)
{
	ssize_t	invld_symbol;
	size_t	op_len;
	char	*op_name;

	op_len = 0;
	if ((op_name = ft_strtrim(ft_strtok(cur_line, DELIMS_CHARS))))
	{
		op_exists(op_name);
		op_len = ft_strlen(op_name);
	}
	else
	{
		ft_printf("ERROR: The [%s] does not exists!!\n", cur_line);
		exit(EXIT_FAILURE);
	}
	if ((invld_symbol = get_invalid_symbols(op_name, op_len, OPS_CHARS)) != -1)
	{
		c->column += (size_t)invld_symbol;
		ft_printf("\x1b[31mLexical error:\x1b[0m Wrong op's name: [%s]\n",\
		op_name);
		exit(EXIT_FAILURE);
	}
	return (op_name);
}

uint8_t			op_get_code(char *op)
{
	uint8_t	op_code;
	ssize_t curr_instr;

	op_code = 0;
	curr_instr = -1;
	while (++curr_instr < NUM_INSTRUCTIONS)
	{
		if (ft_strequ(g_op_template_tab[curr_instr].name, op))
			op_code = g_op_template_tab[curr_instr].code;
	}
	if (op_code == 0)
		semantic_errors(E_UNKNOWN_INSTR, op, NULL);
	return (op_code);
}

uint32_t		op_get_pos(uint32_t pos, uint32_t size)
{
	return (size || pos ? pos + size : 0);
}

uint32_t		op_get_size(t_b_token *b_token)
{
	uint32_t	size;
	ssize_t		curr_arg;

	if (!b_token->op_code)
		return (0);
	size = 1;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (!b_token->args[curr_arg])
			break ;
		if (b_token->args[curr_arg]->code == REG_CODE)
			size += 1;
		else if (b_token->args[curr_arg]->code == DIR_CODE)
			size += b_token->args[curr_arg]->dir_size;
		else if (b_token->args[curr_arg]->code == IND_CODE)
			size += 2;
	}
	if (curr_arg >= 1 && b_token->codage)
		size += 1;
	return (size);
}
