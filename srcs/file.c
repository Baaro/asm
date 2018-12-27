/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:54 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:55 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_file	*file_new(void)
{
	return (ft_memalloc(sizeof(t_file)));
}

void			file_del(t_file **f)
{
	free((*f)->name);
	free((*f)->data);
	free((*f)->line);
	close((*f)->fd);
	free(*f);
}

static void		check_endline(char *line, ssize_t size)
{
	while (--size)
	{
		if (ft_isalnum(line[size]))
		{
			while (--size)
			{
				if (is_endline(line[size]) && is_comment(line[size + 1]))
					return ;
				if (is_endline(line[size]) && !is_comment(line[size + 1]))
					lexical_errors(E_NO_ENDLINE, NULL);
			}
		}
		else if (is_endline(line[size]))
			return ;
	}
}

static void		file_check_endline(t_file *file)
{
	ssize_t	ret;
	ssize_t size;
	char	*tmp;
	char	*data;

	tmp = ft_strnew(BUFF_SIZE);
	data = ft_strnew(0);
	size = 0;
	while ((ret = read(file->fd, tmp, BUFF_SIZE)))
	{
		size += ret;
		data = ft_strjoincl(data, tmp, 0);
		ft_strclr(tmp);
	}
	check_endline(data, size);
	ft_strdel(&tmp);
	ft_strdel(&data);
	close(file->fd);
	file->fd = open(file->name, O_RDONLY);
}

t_file			*file_get(char *filename)
{
	t_file	*file;

	if (!ft_is_file(filename))
	{
		ft_printf("ERROR: Can't read source file \"%s\"\n", filename);
		exit(EXIT_FAILURE);
	}
	file = file_new();
	file->name = ft_strdup(filename);
	if ((file->fd = open(file->name, O_RDONLY)) == -1)
	{
		ft_printf("WRONG FILE ON INPUT!\n");
		exit(EXIT_FAILURE);
	}
	file_check_endline(file);
	return (file);
}
