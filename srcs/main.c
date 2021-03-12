/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:30 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/29 20:34:43 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	usage(void)
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>"
			"\n    -a : Instead of creating a .cor file, "
			"outputs a stripped and annotated "
			"version of the code to the standard output.\n");
	exit(EXIT_FAILURE);
}

void	files_del(t_file **f, t_file_cor **fc)
{
	file_del(f);
	file_cor_del(fc);
}

int		main(int ac, char **av)
{
	uint8_t		flag;
	t_file_cor	*fc;
	t_file		*f;
	t_counter	*c;

	if (ac == 1)
		usage();
	else if (ac >= 2)
	{
		c = counter_new();
		flag = flags_get(&ac, &av, c);
		if (ac == c->args)
			usage();
		while (c->args < ac)
		{
			f = file_get(av[c->args]);
			fc = file_cor_make(f, c);
			file_cor_write(fc, flag);
			files_del(&f, &fc);
			counter_clear(c);
			c->args++;
		}
		counter_del(&c);
	}
	return (EXIT_SUCCESS);
}
