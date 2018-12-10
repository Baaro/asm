#include "libft.h"

void		ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *last;

	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}