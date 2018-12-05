#include "asm.h"

t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	0,	{T_DIR},												4,	live_compute},
	{"ld",		2,	0,	{T_DIR | T_IND, T_REG},									4,	ld_compute},
	{"st",		3,	0,	{T_REG, T_IND | T_REG},									4,	st_compute},
	{"add",		4,	0,	{T_REG, T_REG, T_REG},									4,	add_compute},
	{"sub",		5,	0,	{T_REG, T_REG, T_REG},									4,	sub_compute},	
	{"and",		6,	0,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	and_compute},
	{"or",		7,	0,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	or_compute},
	{"xor",		8,	0,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	xor_compute},
	{"zjmp",	9,	0,	{T_DIR},												2,	zjmp_compute},
	{"ldi",		10,	0,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	ldi_compute},
	{"sti",		11,	0,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2,	sti_compute},
	{"fork",	12,	0,	{T_DIR},												2,	fork_compute},
	{"lld",		13,	0,	{T_DIR | T_IND, T_REG},									4,	lld_compute},
	{"lldi", 	14,	0,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	lldi_compute},
	{"lfork",	15,	0,	{T_DIR},												2,	lfork_compute},
	{"aff",		16,	0,	{T_REG},												4,	aff_compute},
	{0, 		0,	0,	{0}}
};
// byte_code = g_instrs_tab[current_instr].make_bytecode(token);

void			ft_lstprint(t_list *elem)
{
	if (elem)
		ft_printf("%s\n", elem->content);
}

void			token_print(t_list *token)
{
	ssize_t i;

	printf("\n-----------TOKEN-----------\n");
	printf("LABELS:\n");
	ft_lstiter((*(t_token *)token->content).labels, ft_lstprint);
	printf("INSTRUCTION: [%s]\n", (*(t_token*)token->content).instr);
	printf("ARGUMENTS:\n");
	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		printf("arg[%zu] -> %s\n", i, (*(t_token*)token->content).args[i]);
	printf("\n-----------TOKEN-----------\n");
}

ssize_t			get_invalid_symbols(char *line, size_t len)
{
	ssize_t	i;

	i = -1;
	while (line[++i] && i < (ssize_t)len)
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
			return(i);
	}
	return (i == len ? -1 : i);
}

void			get_arguemnts(t_token *token)
{
	ssize_t	i = -1;
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

void    		append_token(t_list **token_head, t_token *token)
{
	ft_lstaddend(token_head, ft_lstnew(token, sizeof(t_token)));
	// free(label);
}

t_token 		*new_token(t_list *labels, char *fline, t_counter *counter)
{
	t_token		*token;
	char		*label;
	size_t		label_len;

	token = ft_memalloc(sizeof(t_token));
	if ((label = get_label(fline, counter))) // label with instr
	{
		label_len = ft_strlen(label);
		append_label(&labels, label, label_len);
		token->instr = get_instruction(fline, fline + label_len + 1, counter);
	}
	else // instr without label
		token->instr = get_instruction(fline, fline, counter);
	token->labels = ft_lstmap(labels, ft_lstcopy);
	get_arguemnts(token);
	return (token);
}
// void			token_free(t_token **token) // does not work
// {
// 	ssize_t	i = -1;

// 	ft_lstdel(&(*token)->labels, ft_lstelemfree);
// 	ft_strdel(&(*token)->instr);
// 	while (++i < MAX_ARGS_NUMBER - 1)
// 		ft_strdel(&(*token)->args[i]);
// }

void			tokenizer(t_file *file, t_lists *lists, t_counter *counter) // test version
{
	t_token		*token;
	char 		*label;
	size_t		label_len;

	while (file_get_line(file, counter) == 1)
	{
		if ((label = get_solo_label(file->line, counter)))
		{
			label_len = ft_strlen(label);
			append_label(&lists->labels, label, label_len);
		}
		else
		{
			token = new_token(lists->labels, file->line, counter);
			append_token(&lists->tokens, token);
			// token_free(&token);
			ft_lstdel(&lists->labels, ft_lstelemfree);
			// append_linker_label(&lists->link_labels, token);
			// append_linker_refs(&lists->link_refs, token);
		}
	}
	ft_lstiter(lists->tokens, token_print);
}
