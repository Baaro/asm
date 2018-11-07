/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 21:13:23 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/04 17:46:06 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_lststrlen(t_list *list)
{
	size_t				res;

	res = 0;
	while (list)
	{
		res += ft_strlen(list->content);
		list = list->next;
	}
	return (res);
}

void		ft_write_remnant(t_list **mem, t_list *curr, int fd)
{
	t_list				*list;
	int					i;

	list = *mem;
	i = 0;
	while (((char*)curr->content)[i] != '\n' && ((char*)curr->content)[i])
		i++;
	if (((char*)curr->content)[i])
	{
		i++;
	}
	while (list)
	{
		if ((int)list->content_size == fd)
		{
			free(list->content);
			list->content = ft_strdup((char*)curr->content + i);
			break ;
		}
		list = list->next;
	}
}

char		*ft_lstdraw(t_list *list, t_list **mem, int fd, int ret)
{
	char				*res;
	char				*tmp;
	t_list				*lst;
	size_t				j;

	lst = (*mem);
	while ((int)lst->content_size != fd)
		lst = lst->next;
	CHECK0(!(res = (char*)malloc(sizeof(char) * (ft_lststrlen(list) + 1))));
	tmp = res;
	while (list)
	{
		j = 0;
		while (list->content_size > j + 1 && ((char*)list->content)[j] != '\n')
			*tmp++ = ((char*)list->content)[j++];
		if (((char*)list->content)[j] == '\n')
			if (j + 1 < list->content_size)
				ft_write_remnant(&lst, list, fd);
		list = list->next;
	}
	if (!ret)
		ft_bzero(lst->content, 1);
	*tmp = '\0';
	return (res);
}

t_list		*ft_check_file(t_list **mem, int fd)
{
	t_list				*tmp;
	t_list				*tmp2;
	void				*str;

	tmp = *mem;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			tmp2 = ft_lstnew(tmp->content, ft_strlen((char*)tmp->content) + 1);
			return (tmp2);
		}
		tmp = tmp->next;
	}
	str = ft_memalloc(1);
	tmp = ft_lstnew(str, fd);
	tmp2 = ft_lstnew(str, 1);
	free(str);
	ft_lstadd(mem, tmp);
	return (tmp2);
}

int			get_next_line(const int fd, char **line)
{
	size_t				ret;
	char				*buf;
	static t_list		*mem;
	t_list				*ls;
	int					i;

	CHECK1((buf = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))));
	CHECK1(!(fd < 0 || !line || read(fd, buf, 0) < 0));
	ls = ft_check_file(&mem, fd);
	if (!(ft_strchr(ls->content, '\n')))
		while ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			ft_lstaddback(&ls, ft_lstnew(buf, ret + 1));
			if (ft_strchr(buf, '\n'))
				break ;
		}
	else
		ret = ls->content_size;
	i = (int)ft_lststrlen(ls);
	*line = ft_lstdraw(ls, &mem, fd, ret);
	ft_lstdel(&ls, NULL);
	free(buf);
	CHECK0(ret == 0 && i == 0);
	return (1);
}
