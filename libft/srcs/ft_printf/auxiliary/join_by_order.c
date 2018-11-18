/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_by_order.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:40:21 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/05 18:40:22 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*output_by_order(char *s1, char *s2, char *s3, char *s4)
{
	char	*s1_s2;
	char	*s3_s4;
	char	*new;

	s1_s2 = NULL;
	s3_s4 = NULL;
	new = NULL;
	if (!(s1_s2 = ft_strjoincl(s1, s2, 1)))
		return (NULL);
	if (!(s3_s4 = ft_strjoincl(s3, s4, 1)))
		return (NULL);
	new = ft_strjoincl(s1_s2, s3_s4, 1);
	return (new);
}
