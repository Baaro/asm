/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 17:09:38 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/05 17:09:40 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	correct_flags_integer(t_arg **arg)
{
	if (ARG.flags[HESH])
		ARG.flags[HESH] = 0;
	if (ARG.flags[SPACE] && ARG.flags[PLUS])
		ARG.flags[SPACE] = 0;
	if (ARG.precision >= 0 || ARG.flags[MINUS])
		ARG.flags[ZERO] = 0;
	if (ARG.flags[NEGATIVE])
		ARG.flags[PLUS] = 0;
}

static void	correct_flags_octal_hexa(t_arg **arg)
{
	if (ARG.flags[PLUS])
		ARG.flags[PLUS] = 0;
	if (ARG.flags[SPACE])
		ARG.flags[SPACE] = 0;
	if (ARG.precision >= 0 || ARG.flags[MINUS])
		ARG.flags[ZERO] = 0;
}

static void	correct_flags_unsigned(t_arg **arg)
{
	if (ARG.flags[PLUS])
		ARG.flags[PLUS] = 0;
	if (ARG.flags[SPACE])
		ARG.flags[SPACE] = 0;
	if (ARG.flags[HESH])
		ARG.flags[HESH] = 0;
	if (ARG.precision >= 0 || ARG.flags[MINUS])
		ARG.flags[ZERO] = 0;
}

void		correct_flags(t_arg **arg)
{
	if (ARG.type == 'd' || ARG.type == 'i' || ARG.type == 'D')
		correct_flags_integer(arg);
	else if (ARG.type == 'o' || ARG.type == 'O'
	|| ARG.type == 'X' || ARG.type == 'x')
		correct_flags_octal_hexa(arg);
	else if (ARG.type == 'u')
		correct_flags_unsigned(arg);
}
