/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_get_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:08 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:10 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool		is_endline(char c)
{
	return (!c || c == '\n');
}

bool		is_comment(char c)
{
	return (c == ';' || c == '#');
}

static char	*file_append_data(char **data, char **line, bool is_cmds)
{
	char	*without_endline;
	char	*with_endline;

	without_endline = *data == NULL ? ft_strnew(0) : *data;
	without_endline = ft_strjoincl(without_endline, *line, 0);
	if (is_cmds)
		*line = ft_strjoincl(*line, "\n", 0);
	with_endline = ft_strjoincl(without_endline, "\n", 0);
	*data = with_endline;
	return (*data);
}

int			file_get_line(t_file *f, t_counter *c, bool is_cmds)
{
	int	status;

	while ((status = get_next_line(f->fd, &f->line) == 1))
	{
		c->row++;
		c->column = 0;
		c->begin_whitespaces = ft_strspn(f->line, DELIMS_CHARS);
		if (!is_cmds && *(f->line + c->begin_whitespaces) != HEADER_DOT_CHAR)
		{
			if (is_endline(f->line[c->begin_whitespaces])
			|| is_comment(f->line[c->begin_whitespaces]))
				continue ;
			f->line = ft_strcutuntil(f->line, COMMENT_CHARS);
		}
		f->data = file_append_data(&f->data, &f->line, is_cmds);
		break ;
	}
	return (status);
}
