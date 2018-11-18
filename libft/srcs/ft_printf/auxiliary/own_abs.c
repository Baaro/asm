#include "ft_printf.h"

intmax_t    own_abs(intmax_t val)
{
    return ((val < 0) ? -val : val);
}