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

t_file			*file_get(char *filename)
{
	t_file	*file;
	char	*slash;

	if (!ft_is_file(filename))
	{
		if ((slash = ft_strrchr(filename, '/')))
			ft_printf("ERROR: Can't read source file\
			[%s]\n", ft_strsub(slash + 1, 0, ft_strlen(slash)));
		else
			ft_printf("ERROR: Can't read source file [%s]\n", filename);
		exit(EXIT_FAILURE);
	}
	file = file_new();
	file->name = ft_strdup(filename);
	if ((file->fd = open(file->name, O_RDONLY)) == -1)
	{
		ft_printf("WRONG FILE ON INPUT!\n");
		exit(EXIT_FAILURE);
	}
	return (file);
}
