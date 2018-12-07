#include "asm.h"

static void	cmd_str_del(t_cmd_str **str)
{
	free((*str)->value);
	free(*str);
}

static void	cmd_str_save(t_header *h, t_cmd_str *str, t_counter *c)
{
	size_t	after_end_quotes;
	char	*new_str;

	new_str = NULL;
	after_end_quotes = c->column + str->len + 1;
	after_end_quotes += ft_strspn(str->value + after_end_quotes, DELIMS_CHARS);
	after_end_quotes += ft_strspn(str->value + after_end_quotes, "\n");
	if (str->value[after_end_quotes] != '\0'
	&& str->value[after_end_quotes] != COMMENT_CHAR
	&& str->value[after_end_quotes] != COMMENT_CHAR_ALT)
		lexical_errors(E_INVALID_SYMBOLS, str->value, c);
	new_str = ft_strsub(str->value, c->column, str->len - 1);
	if (h->is_name_cmd)
		ft_strncpy(h->prog_name, new_str, str->len);
	else if (h->is_comment_cmd)
		ft_strncpy(h->comment, new_str, str->len);
}

static char	*cmd_str_read(t_file *f, t_counter *c)
{
	char *str;

	str = ft_strdup(f->line + c->column + 1);
	str = ft_strjoincl(str, "\n", 0);
	while (!(ft_strchr(str, QUOTES_CHAR)))
	{
		if ((file_get_line(f, c, 1)) == 0)
			lexical_errors(E_IS_NOT_ENOUGH_DATA, f->line, c);
		str = ft_strjoincl(str, f->line, 0);
	}
	return (str);
}

static void	cmd_str_valid(t_file *f, t_header *h, t_cmd_str *str, t_counter *c)
{
	while (str->len <= str->maxlen
	&& str->value[str->len] != QUOTES_CHAR)
	{
		if (str->len == str->maxlen)
		{
			if (h->is_name_cmd)
				lexical_errors(E_CHAMPION_NAME_TOO_LONG, f->line, c);
			else if (h->is_comment_cmd)
				lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, f->line, c);
		}
		if (str->value[str->len + 1] == '\0')
		{
			c->column += str->len + 2;
			lexical_errors(E_NO_END_QUOTES, f->line, c);
		}
		str->len++;
	}
}

void		cmd_str_set(t_file *f, t_header *h, t_counter *c)
{
	t_cmd_str	*str;

	str = ft_memalloc(sizeof(t_cmd_str));
	if (h->is_name_cmd)
	{
		if (h->prog_name[0])
			semantic_errors(E_DOUBLE_NAME, f->line, c);
		str->maxlen = PROG_NAME_LENGTH + 1;
		c->column += c->begin_whitespaces + ft_strlen(NAME_CMD_STR);
	}
	else if (h->is_comment_cmd)
	{
		if (h->comment[0])
			semantic_errors(E_DOUBLE_COMMENT, f->line, c);
		str->maxlen = COMMENT_LENGTH + 1;
		c->column += c->begin_whitespaces + ft_strlen(COMMENT_CMD_STR);
	}
	c->column += ft_strspn(f->line + c->column, DELIMS_CHARS);
	if (f->line[c->column] != QUOTES_CHAR)
		lexical_errors(E_NO_BEGIN_QUOTES, f->line, c);
	str->value = cmd_str_read(f, c);
	cmd_str_valid(f, h, str, c);
	cmd_str_save(h, str, c);
	h->is_name_cmd = false;
	h->is_comment_cmd = false;
	cmd_str_del(&str);
}
