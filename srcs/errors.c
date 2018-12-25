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

void	lexical_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Lexical errors can be:
	**
	**  [+] 1. The name's or comment's string does not have BEGIN quotes -> " <-;
	**  [+] 2. The name's or comment's string does not have END quotes -> " <-;
	**  [+] 3. Unmatched command;
	**  [+] 4. Exceeding length of name's or comment's string
	**         (strlen(string) > PROG_NAME_LENGTH(if name) || strlen(string) > COMMENT_LENGTH(if comment));
	**  [+] 5. Appearance of illegal characters at the tail of string.
	*/
	ft_printf("\x1b[31mLexical error: \x1b[0m");
	if (counter)
		ft_printf("[%zu:%zu]", counter->row, get_currunet_column(counter));
	if (error == E_NO_BEGIN_QUOTES)
		ft_printf("The name's of string doesn't have BEGIN quotes!\n");
	else if (error == E_NO_END_QUOTES)
		ft_printf("The name's of string doesn't have END quotes!\n");
	else if (error == E_CHAMPION_NAME_TOO_LONG)
		ft_printf("Champion name too long!\n");
	else if (error == E_CHAMPION_COMMENT_TOO_LONG)
		ft_printf("Champion comment too long!\n");
	else if (error == E_INVALID_SYMBOLS)
		ft_printf("Invalid symbol!\n");
	else if (error == E_WRONG_INPUT)
		ft_printf("Wrong input!\n");
	else if (error == E_IS_NOT_ENOUGH_DATA)
		ft_printf("Doesn't enough data for compile\n");
	exit(EXIT_FAILURE);
}

void	syntactic_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Syntax errors:
	**
	**  [-] 1. Missing one of the separators(' ' && ',') in instruction definition;
	**  [-] 2. Misspelled keywords;
	**
	*/
	line = NULL;
	ft_printf("\x1b[31mSyntactic error\x1b[0m");
	ft_printf("[%zu:%zu]\n", counter->row, get_currunet_column(counter));
	if (error == E_NOT_ALL_COMMAND)
		ft_printf("Is not a .name or .comment!\n");
	exit(EXIT_FAILURE);
}

void	semantic_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Semantic errors can be:
	**
	**  [-]  1. Unknown instraction;
	**	[+]  2. Double name
	**	[+]  3. Double comment
	**
	*/
	ft_printf("\x1b[31mSemantic error: \x1b[0m");
	if (counter)
		ft_printf("[%zu:%zu]", counter->row, get_currunet_column(counter));
	if (error == E_DOUBLE_NAME)
		ft_printf("The Name command has already read!\n");
	else if (error == E_DOUBLE_COMMENT)
		ft_printf("The Comment command has already read!\n");
	else if (error == E_UNMATCHED_COMMAND)
		ft_printf("Unmatched command!\n");
	else if (error == E_COMMAND_READ)
		ft_printf("The Commands has already read! This is an unknown command!\n");
	else if (error == E_SEMANTIC_ERROR)
		ft_printf("Semantic error!\n");
	else if (error == E_UNKNOWN_INSTR)
		ft_printf("Unknown instruction: [%s]!\n", line);
	else if (error == E_WRONG_ARGUMENT)
		ft_printf("Unknown argument: [%s]!\n", line);
	exit(EXIT_FAILURE);
}

// void	linker_errors(t_errors error, char *line, t_counter *counter)
// {
// 	/*
// 	**      Linker errors can be:
// 	**
// 	**      1. No definition of label
// 	**      2. No declaration of label
// 	**
// 	*/
// 	exit(EXIT_FAILURE);
// }
