/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:04:49 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/25 18:43:43 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_buffer_char(t_pr *pr, char c)
{
	if (!pr->buff)
	{
		pr->size = 1;
		pr->buff = (char*)ft_memalloc(sizeof(char));
	}
	if (pr->buff_len == pr->size)
		ft_realloc(pr);
	pr->buff[pr->buff_len++] = c;
}

void	ft_buffer(t_pr *pr, char *str, size_t size)
{
	if (!pr->buff)
	{
		pr->size = size + 1;
		pr->buff = (char*)ft_memalloc(pr->size);
	}
	while ((pr->buff_len + size) >= pr->size)
		ft_realloc(pr);
	pr->buff = ft_memcpy(&pr->buff[pr->buff_len], str, size) - pr->buff_len;
	pr->buff_len += size;
}

int		ft_print_main(int fd, t_pr *pr)
{
	while (*pr->format)
	{
		if (*pr->format == '%')
		{
			pr->format++;
			if (!*pr->format)
				break ;
			ft_parse(pr);
		}
		else
			ft_buffer(pr, pr->format, 1);
		pr->format++;
	}
	write(fd, pr->buff, pr->buff_len);
	return (0);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	t_pr		*pr;
	int			i;

	pr = (t_pr*)ft_memalloc(sizeof(t_pr));
	pr->format = (char *)format;
	va_start(pr->list, format);
	ft_print_main(fd, pr);
	i = pr->buff_len;
	free(pr->buff);
	free(pr);
	va_end(pr->list);
	return (i);
}

int		ft_printf(const char *format, ...)
{
	t_pr		*pr;
	int			i;

	pr = (t_pr*)ft_memalloc(sizeof(t_pr));
	pr->format = (char *)format;
	va_start(pr->list, format);
	ft_print_main(1, pr);
	i = pr->buff_len;
	free(pr->buff);
	free(pr);
	va_end(pr->list);
	return (i);
}
