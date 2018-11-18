#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>

bool	ft_is_dir(const char* filename)
{
    struct stat buf;

    stat(filename, &buf);
    return S_ISDIR(buf.st_mode);
}
