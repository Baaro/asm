#include "libft.h"

void		ft_lstelemfree(void *content, size_t content_size)
{
	if (content)
		ft_memdel(&content);
	content_size = 0;
}
