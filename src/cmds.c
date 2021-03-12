/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:32 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:34 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	cmd_str_save(t_header *h, t_cmd_str *str)
{
	if (h->is_name_cmd)
	{
		ft_memset(h->prog_name, 0, PROG_NAME_LENGTH);
		ft_strncpy(h->prog_name, str->value, str->len);
	}
	else if (h->is_comment_cmd)
	{
		ft_memset(h->comment, 0, COMMENT_LENGTH);
		ft_strncpy(h->comment, str->value, str->len);
	}
}

static char	*cmd_str_read(t_file *f, t_counter *c)
{
	char *str;

	str = ft_strdup(f->line + c->column + 1);
	str = ft_strjoincl(str, "\n", 0);
	while (!(ft_strchr(str, QUOTES_CHAR)))
	{
		if ((file_get_line(f, c, true)) == 0)
			lexical_errors(E_NO_END_QUOTES, c);
		str = ft_strjoincl(str, f->line, 0);
	}
	return (str);
}

static void	cmd_str_valid(t_header *h, t_cmd_str *str, t_counter *c)
{
	size_t	a_end_q;

	while (str->len <= str->maxlen
	&& str->value[str->len] != QUOTES_CHAR)
	{
		if (str->len == str->maxlen)
		{
			if (h->is_name_cmd)
				lexical_errors(E_CHAMPION_NAME_TOO_LONG, c);
			else if (h->is_comment_cmd)
				lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, c);
		}
		if (str->value[str->len + 1] == '\0')
		{
			c->column += str->len + 2;
			lexical_errors(E_NO_END_QUOTES, c);
		}
		str->len++;
	}
	a_end_q = str->len + 1;
	a_end_q += ft_strspn(str->value + a_end_q, DELIMS_CHARS);
	a_end_q += ft_strspn(str->value + a_end_q, "\n");
	if (str->value[a_end_q] && str->value[a_end_q] != COMMENT_CHAR
	&& str->value[a_end_q] != COMMENT_CHAR_ALT)
		lexical_errors(E_INVALID_SYMBOLS, c);
}

static void	cmd_str_manage(t_file *f, t_header *h, t_cmd_str *s, t_counter *c)
{
	s->value = cmd_str_read(f, c);
	cmd_str_valid(h, s, c);
	cmd_str_save(h, s);
}

void		cmd_str_set(t_file *f, t_header *h, t_counter *c)
{
	t_cmd_str	*str;

	str = ft_memalloc(sizeof(t_cmd_str));
	if (h->is_name_cmd)
	{
		if (h->prog_name[0])
			semantic_errors(E_DOUBLE_NAME, f->line, c);
		str->maxlen = PROG_NAME_LENGTH + 1;
		c->column += c->begin_whitespaces + ft_strlen(NAME_CMD_STR);
	}
	else if (h->is_comment_cmd)
	{
		if (h->comment[0])
			semantic_errors(E_DOUBLE_COMMENT, f->line, c);
		str->maxlen = COMMENT_LENGTH + 1;
		c->column += c->begin_whitespaces + ft_strlen(COMMENT_CMD_STR);
	}
	c->column += ft_strspn(f->line + c->column, DELIMS_CHARS);
	if (f->line[c->column] != QUOTES_CHAR)
		lexical_errors(E_NO_BEGIN_QUOTES, c);
	cmd_str_manage(f, h, str, c);
	h->is_name_cmd = false;
	h->is_comment_cmd = false;
	free(str->value);
	ft_memdel((void**)&str);
}
