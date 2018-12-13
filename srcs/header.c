#include "asm.h"

static t_header	*header_new(void)
{
	return (ft_memalloc(sizeof(t_header)));
}

static bool		is_dot_char(char *c)
{
	return (*c == HEADER_DOT_CHAR);
}

static void		header_set_cmds(t_file *f, t_header *h, t_counter *c)
{
	while ((file_get_line(f, c, false)) == 1)
	{
		if (is_dot_char(f->line + c->begin_whitespaces))
		{
			if (ft_strnequ(f->line, NAME_CMD_STR, ft_strlen(NAME_CMD_STR)))
				h->is_name_cmd = true;
			else if (ft_strnequ(f->line, COMMENT_CMD_STR, ft_strlen(COMMENT_CMD_STR)))
				h->is_comment_cmd = true;
			else
				semantic_errors(E_UNMATCHED_COMMAND, f->line, c);
			cmd_str_set(f, h, c);
			return ;
		}
		else
			semantic_errors(E_SEMANTIC_ERROR, f->line, c);
	}
	lexical_errors(E_IS_NOT_ENOUGH_DATA, NULL, c);
}

void			header_del(t_header **h)
{
	ft_memdel((void **)h);
}

t_header		*header_get(t_file *f, t_counter *c)
{
	t_header    *h;
	ssize_t		h_cmds;

	h = header_new();
	h_cmds = -1;
	while (++h_cmds != VALID)
		header_set_cmds(f, h, c);
	return (h);
}