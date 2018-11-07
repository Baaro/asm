/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:13 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/07 17:33:15 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR
# define COREWAR

# include "ft_printf.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define CYAN "\033[0;36m"
# define LGRAY "\033[0;37m"
# define NC "\033[0m"
# define PRED(X) ft_printf(RED "%s" NC,X)
# define PGREEN(X) ft_printf(GREEN "%s" NC,X)
# define PYELLOW(X) ft_printf(YELLOW "%s" NC,X)
# define PBLUE(X) ft_printf(BLUE "%s" NC,X)
# define PPINK(X) ft_printf(PINK "%s" NC,X)
# define PCYAN(X) ft_printf(CYAN "%s" NC,X)

# define C_FLAG_1		(1 << 0)
# define C_FLAG_2		(1 << 1)
# define C_FLAG_3		(1 << 2)
# define C_FLAG_4		(1 << 3)
# define C_FLAG_5		(1 << 4)

typedef struct		s_corewar
{
	int				fl;
	char			*name;
}					t_corewar;

#endif
