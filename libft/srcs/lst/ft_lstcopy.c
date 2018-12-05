#include "libft.h"

t_list	*ft_lstcopy(t_list *elem)
{
	t_list *copy;

	if (!elem)
		return (NULL);
	if (!(copy = ft_lstnew(elem->content, elem->content_size)))
		return (NULL);
	return (copy);
}