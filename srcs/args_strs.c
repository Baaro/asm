/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:37:49 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:37:50 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void			args_valid_all_str(char *arg, t_counter *c)
{
	ssize_t	invalid_symbol;
	size_t	arglen;
	size_t	coma;

	arglen = ft_strlen(arg);
	if ((invalid_symbol = get_invalid_symbols(arg, arglen, ARGS_CHARS)) != -1)
	{
		c->column += arglen + (size_t)invalid_symbol - 1;
		lexical_errors(E_INVALID_SYMBOLS, c);
	}
	coma = 0;
	while (*arg)
	{
		if (*arg == ',')
			coma++;
		if (coma > 2 || (*arg == ',' && *(arg + 1) == ','))
			lexical_errors(E_INVALID_SYMBOLS, c);
		arg++;
	}
}

void				args_valid_begin_char(char args_begin)
{
	if (!(ft_strchr(VALID_CHARS, args_begin)))
	{
		ft_printf("ERROR: Wrong separator %c\n", args_begin);
		exit(EXIT_FAILURE);
	}
}

void				args_valid_end_char(char args_begin)
{
	if (!(ft_strchr(VALID_CHARS, args_begin)))
	{
		ft_printf("ERROR: wrong separator %c\n", args_begin);
		exit(EXIT_FAILURE);
	}
}

void				args_get_strs(t_token *token, t_counter *c)
{
	ssize_t	args_counter;
	char	*args_str;

	if ((args_str = ft_strtrim(ft_strtok(NULL, "\0"))))
	{
		args_valid_all_str(args_str, c);
		args_valid_begin_char(*args_str);
		args_valid_end_char(args_str[ft_strlen(args_str) - 1]);
		args_counter = 0;
		token->args[args_counter] = ft_strtrim(ft_strtok(args_str, ","));
		while (++args_counter < MAX_ARGS_NUMBER)
			token->args[args_counter] = ft_strtrim(ft_strtok(NULL, ","));
		free(args_str);
	}
	else
	{
		ft_printf("ERROR: [%s] has no argumets!\n", token->op);
		exit(EXIT_FAILURE);
	}
}
