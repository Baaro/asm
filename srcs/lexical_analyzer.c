#include "info.h"

void	lexical_analyze(const t_info *i, const t_file *f, t_stck_tkns **st) // test version
{
	unsigned int	column;
	unsigned int	row;

	column = 0;
	row = 0;
	valid_header(f->data, &row, &column);
	// tokenizing_instructions();
}
