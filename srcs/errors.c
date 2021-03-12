/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:47 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:48 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lexical_errors(t_errors error, t_counter *counter)
{
	ft_printf("\x1b[31mLexical error:\x1b[0m");
	if (counter)
		ft_printf("[%zu]", counter->row);
	if (error == E_NO_BEGIN_QUOTES)
		ft_printf("The cmd's string doesn't have BEGIN quotes!\n");
	else if (error == E_NO_END_QUOTES)
		ft_printf("The cmd's string doesn't have END quotes!\n");
	else if (error == E_CHAMPION_NAME_TOO_LONG)
		ft_printf("Champion name too long!\n");
	else if (error == E_CHAMPION_COMMENT_TOO_LONG)
		ft_printf("Champion comment too long!\n");
	else if (error == E_INVALID_SYMBOLS)
		ft_printf("Wrong character!\n");
	else if (error == E_WRONG_INPUT)
		ft_printf("Wrong input!\n");
	else if (error == E_IS_NOT_ENOUGH_DATA)
		ft_printf("Doesn't enough data for compile\n");
	else if (error == E_NO_ENDLINE)
		ft_printf("Syntax error - unexpected end of input \
(Perhaps you forgot to end with a newline ?)\n");
	exit(EXIT_FAILURE);
}

void	syntactic_errors(t_errors error, char *line, t_counter *counter)
{
	line = NULL;
	ft_printf("\x1b[31mSyntactic error:\x1b[0m");
	ft_printf("[%zu] ", counter->row);
	if (error == E_NOT_ALL_COMMAND)
		ft_printf("Is not a .name or .comment!\n");
	else if (E_WRONG_LABEL_NAME)
		ft_printf("Wrong label's name!\n", line);
	exit(EXIT_FAILURE);
}

void	semantic_errors(t_errors error, char *line, t_counter *counter)
{
	ft_printf("\x1b[31mSemantic error:\x1b[0m");
	if (counter)
		ft_printf("[%zu]", counter->row);
	if (error == E_DOUBLE_NAME)
		ft_printf("The Name command has already read!\n");
	else if (error == E_DOUBLE_COMMENT)
		ft_printf("The Comment command has already read!\n");
	else if (error == E_UNMATCHED_COMMAND)
		ft_printf("Unknown command!\n");
	else if (error == E_COMMAND_READ)
		ft_printf("The Commands has already read\
		This is an unknown command!\n");
	else if (error == E_SEMANTIC_ERROR)
		ft_printf("Semantic error!\n");
	else if (error == E_UNKNOWN_INSTR)
		ft_printf("Unknown instruction: [%s]!\n", line);
	else if (error == E_WRONG_ARGUMENT)
		ft_printf("Wrong argument for instruction: [%s]!\n", line);
	exit(EXIT_FAILURE);
}

void	linker_errors(t_errors error, char *line)
{
	ft_printf("\x1b[31mLinker error: \x1b[0m");
	if (error == E_UNKNOWN_REFERENCE)
		ft_printf("Unexisting reference: [%s]!\n", line);
	exit(EXIT_FAILURE);
}
