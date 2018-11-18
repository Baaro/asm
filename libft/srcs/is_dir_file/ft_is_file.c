#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>

bool	ft_is_file(const char* filename)
{
    struct stat buf;

    stat(filename, &buf);
    return (S_ISREG(buf.st_mode));
}
