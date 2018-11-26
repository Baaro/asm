#include "../../includes/libft.h"

void	ft_putnchar(char c, size_t len)
{
	while (len--)
		if (ft_isascii(c))
			write(1, &c, 1);
}
