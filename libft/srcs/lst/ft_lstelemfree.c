#include "libft.h"

void		ft_lstelemfree(void *content, size_t content_size)
{
	if (content)
	{
		ft_memset(content, 0, content_size);
		ft_memdel(&content);
	}
}
