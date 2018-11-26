#include "asm.h"

void	point_to_mistake(char *line, size_t column, char symb)
{
	size_t	spaces;
	size_t	waved_line;

	waved_line = 0;
	spaces = 0;
	ft_printf("%s\n", line);
	while (++spaces < column)
		ft_printf(" ");
	ft_printf("\x1b[33m^ ");
	while (line[++waved_line + spaces])
		ft_printf("~");
	ft_printf("\n");
	spaces = 0;
	while (++spaces < column)
		ft_printf(" ");
	if (symb)
		ft_printf("%c\n", symb);
	ft_printf("\x1b[0m");
}

void    lexical_errors(t_errors error, char *line, t_counter *counter)
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
	if (error == E_NO_BEGIN_QUOTES)
	{
		ft_printf("\x1b[31mLexical error\x1b[0m[%zu:%zu]: The name's of string doesn't have BEGIN quotes!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, STRING_QUOTES_CHAR);
	}
	else if (error == E_NO_END_QUOTES)
	{
		ft_printf("\x1b[31mLexical error\x1b[0m[%zu:%zu]: The name's of string doesn't have END quotes!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, STRING_QUOTES_CHAR);
	}
	else if (error == E_CHAMPION_NAME_TOO_LONG)
		ft_printf("\x1b[31mLexical_error\x1b[0m[%zu:%zu]: Champion name too long!\n", counter->row, counter->column);
	else if (error == E_CHAMPION_COMMENT_TOO_LONG)
		ft_printf("\x1b[31mLexical_error\x1b[0m[%zu:%zu]: Champion comment too long!\n", counter->row, counter->column);
	else if (error == E_WRONG_TAIL_OF_STRING)
	{
		ft_printf("\x1b[31mLexical_error\x1b[0m[%zu:%zu]: Wrong symbol!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, ENDSTRING_CHAR);
	}
	else if (error == E_WRONG_INPUT)
		ft_printf("\x1b[31mLexical_error\x1b[0m[%zu:%zu]: Wrong input!\n");
	else if (error == E_IS_NOT_ENOUGH_DATA)
		ft_printf("\x1b[31mLexical_error\x1b[0m[%zu:%zu]: Doesn't enough data for compile [%s].\n", counter->row, counter->column, line);
	exit(EXIT_FAILURE);
}

void    syntactic_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Syntax errors:
	**
	**  [-] 1. Missing one of the separators(' ' && ',') in instruction definition;
	**  [-] 2. Misspelled keywords;
	**
	*/
	if (error == E_NOT_ALL_COMMAND)
	{
		ft_printf("\x1b[31mSyntactic error\x1b[0m[%zu:%zu]: Is not a .name or .comment!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, ENDSTRING_CHAR);
	}
	exit(EXIT_FAILURE);
}

void    semantic_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Semantic errors can be:
	**
	**  [-]  1. Unknown instraction;
	**	[+]  2. Double name
	**	[+]  3. Double comment
	**
	*/
	if (error == E_DOUBLE_NAME)
		ft_printf("\x1b[31mSemantic error\x1b[0m[%zu:%zu]: The Name command has already read!\n", counter->row, counter->column);
	else if (error == E_DOUBLE_COMMENT)
		ft_printf("\x1b[31mSemantic error\x1b[0m[%zu:%zu]: The Comment command has already read!\n", counter->row, counter->column);
	else if (error == E_UNMATCHED_COMMAND)
	{
		ft_printf("\x1b[31mSemantic error\x1b[0m[%zu:%zu]: Unmatched command!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, ENDSTRING_CHAR);
	}
	else if (error == E_COMMAND_READ)
	{
		ft_printf("\x1b[31mSemantic error\x1b[0m[%zu:%zu]: The Commands has already read! This is an unknown command!\n", counter->row, counter->column);
		point_to_mistake(line, counter->column, ENDSTRING_CHAR);
	}
	exit(EXIT_FAILURE);
}

void    linker_errors(t_errors error, char *line, t_counter *counter)
{
	/*
	**      Linker errors can be:
	**
	**      1. No definition of label
	**      2. No declaration of label
	**
	*/

	exit(EXIT_FAILURE);
}
