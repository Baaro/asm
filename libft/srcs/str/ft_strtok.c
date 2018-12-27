/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:25:30 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/28 00:25:31 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtok(char *s, const char *delimiters)
{
	static char *s_save = "";

	return (ft_strtok_r(s, delimiters, &s_save));
}
