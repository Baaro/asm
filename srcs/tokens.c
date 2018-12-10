#include "asm.h"

// t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
// {
// 	{"live",	1,	{T_DIR},												4,	live_compute},
// 	{"ld",		2,	{T_DIR | T_IND, T_REG},									4,	ld_compute},
// 	{"st",		3,	{T_REG, T_IND | T_REG},									4,	st_compute},
// 	{"add",		4,	{T_REG, T_REG, T_REG},									4,	add_compute},
// 	{"sub",		5,	{T_REG, T_REG, T_REG},									4,	sub_compute},	
// 	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	and_compute},
// 	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	or_compute},
// 	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	xor_compute},
// 	{"zjmp",	9,	{T_DIR},												2,	zjmp_compute},
// 	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	ldi_compute},
// 	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2,	sti_compute},
// 	{"fork",	12,	{T_DIR},												2,	fork_compute},
// 	{"lld",		13,	{T_DIR | T_IND, T_REG},									4,	lld_compute},
// 	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	lldi_compute},
// 	{"lfork",	15,	{T_DIR},												2,	lfork_compute},
// 	{"aff",		16,	{T_REG},												4,	aff_compute},
// 	{0, 		0,	{0}}
// };

// void			token_free(t_token *token) // does not work
// {
// 	ssize_t	i = -1;

// 	if (token->labels)
// 		ft_lstdel(&token->labels, ft_lstelemfree);
// 	// ft_memdel((void**)&token->labels);
// 	ft_strdel(&token->instr);
// 	while (++i < MAX_ARGS_NUMBER - 1)
// 	{
// 		if (token->args[i])
// 			ft_strdel(&token->args[i]);
// 	}
// 	ft_memdel((void**)&token);
// }

void			get_arguemnts(t_token *token)
{
	ssize_t	i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		token->args[i] = ft_strtrim(ft_strtok(NULL, ","));
}

char			*get_instruction(char *fline, char *current_line, t_counter *counter)
{
	ssize_t		invalid_symbol;
	char		*instr;

	instr = ft_strtrim(ft_strtok(current_line, DELIMS_CHARS));
	if ((invalid_symbol = get_invalid_symbols(instr, ft_strlen(instr))) != -1)
	{
		counter->column += ft_strlen(instr) + (size_t)invalid_symbol;
		lexical_errors(E_INVALID_SYMBOLS, fline, counter);
	}
	return (instr);
}

// t_token			*token_copy(token *token)
// {
// 	t_token *new_token;

// 	new_token = ft_memalloc(sizeof(t_token));
// 	new_token	
// }

void			append_token(t_list **token_head, t_token *token)
{
	ft_lstaddend(token_head, ft_lstnew(token, sizeof(t_token)));
	ft_memdel((void**)&token);
}

static t_token	*new_token(t_list *labels, char *fline, t_counter *c)
{
	t_token		*token;
	t_label		*label;

	token = ft_memalloc(sizeof(t_token));
	if ((label = get_label(fline, c)))	/* label with instr */
	{
		append_label(&labels, label);
		token->instr = get_instruction(fline, fline + label->len + 1, c);
	}
	else	/* instr without label */ 
		token->instr = get_instruction(fline, fline, c);
	token->labels = ft_lstmap(labels, ft_lstget);
	get_arguemnts(token);
	return (token);
}


t_list			*tokens_make(t_file *f, t_counter *c) // test version
{
	t_list		*tokens;
	t_list		*labels;
	t_label		*label;

	labels = NULL;
	tokens = NULL;
	while ((file_get_line(f, c, false)) == 1)
	{
		if ((label = get_solo_label(f->line, c)))
			append_label(&labels, label);
		else
		{
			append_token(&tokens, new_token(labels, f->line, c));
			ft_lstdel(&labels, ft_lstelemfree);
		}
	}
	ft_lstiter(tokens, token_print);
	// ft_lstdel(&labels, ft_lstelemfree);
	// ft_memdel((void**)&labels);
    return (tokens);
}
