/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:35:44 by dtsyvin           #+#    #+#             */
/*   Updated: 2017/10/29 22:35:46 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char*)s;
	while (*s)
	{
		if (*s == (char)c)
			tmp = (char*)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	else if (*tmp != (char)c)
		return (0);
	else
		return (tmp);
}
