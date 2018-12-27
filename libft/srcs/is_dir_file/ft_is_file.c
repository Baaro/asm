/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:19:46 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:19:48 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>

bool	ft_is_file(const char *filename)
{
	struct stat buf;

	stat(filename, &buf);
	return (S_ISREG(buf.st_mode));
}
