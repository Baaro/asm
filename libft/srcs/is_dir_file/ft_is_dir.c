/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:19:38 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:19:40 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>

bool	ft_is_dir(const char *filename)
{
	struct stat buf;

	stat(filename, &buf);
	return (S_ISDIR(buf.st_mode));
}
