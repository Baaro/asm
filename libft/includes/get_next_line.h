/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:13:34 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/04 17:46:31 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 20
# define CHECK1(x)	if (!x) return (-1);
# define CHECK0(x)	if (x) return (0);

int			get_next_line(const int fd, char **line);

#endif
