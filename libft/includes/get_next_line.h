/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:16:35 by vsokolog          #+#    #+#             */
/*   Updated: 2018/02/16 01:09:35 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define BUFF_SIZE 8

typedef struct		s_lst
{
	char			*str;
	int				fd;
	struct s_lst	*next;
}					t_lst;

int					get_next_line(const int fd, char **line);
#endif
