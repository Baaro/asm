#include "asm.h"

// void			append_linker_labels(t_lists *lists, t_token *token)
// {
// 	if (token->labels)
// 		append_linker_label(lists->l_labels, token);
// }

// void			append_linker_references(t_lists *lists, t_token *token)
// {
// 	char	*current_reference;
// 	size_t	current_instrument;

// 	current_instrument = -1;
// 	while (++current_instrument < MAX_ARGUMENTS)
// 	{
// 		current_reference = token->instruction.arguments[current_instrument].reference;
// 		if (current_reference)
// 			append_linker_reference(lists->l_refs, token, current_reference);
// 	}

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

void			ft_lstprint(t_list *elem)
{
	if (elem)
		ft_printf("%s\n", elem->content);
}

size_t			valid_line(char *line)
{
	size_t	counter;
	size_t	len;

	counter = -1;
	len = ft_strlen(line);
	while (++counter < len)
	{
		if (!(ft_strchr(VALID_CHARS, line[counter])))
			break ;
	}
	return (counter);
}

size_t			get_instruction(char *line, t_counter *counter)
{
	size_t	instr_iter;
	char	*instr_name;

	counter->column += get_whitespaces(line + counter->column);
	instr_name = ft_strtok(line + counter->column, " \t");
	if ((counter->column += valid_line(instr_iter)) == counter->column)
	{
		instr_iter = -1;
		while (!ft_strequ(instr_name, g_instrs_tab[++instr_iter].name))
			if (instr_iter == NUM_ARGUMENTS + 1)
				semantic_errors(E_UNKNOWN_INSTR, line, counter->column);
	}
	else
		syntactic_errors(E_INVALID_SYMBOLS, line, counter);
	return (instr_iter);
}

t_token			*new_token(char *line, t_counter *counter)
{
	t_token	*token;
	size_t	current_instr;

	token = NULL;
	if ((current_instr = get_instruction(line, counter)))
		token = g_instrs_tab[current_instr].make_token(line, counter);
	else
		lexical_errors(E_UNKNOWN_INSTR, line, counter->column);
	return (token);
}

void			tokenizer(t_file *file, t_lists *lists, t_counter *counter) // test version
{
	t_token		*token;

	token = NULL;
	while (file_get_line(file, counter) == 1)
	{
		if (is_label_without_instruction(file->line, counter))
			append_label(&lists->labels, new_label(file->line, counter));
		else
		{
			if (label_exists(file->line))
				append_label(&lists->labels, new_label(file->line, counter));
			token = new_token(file->line, counter);
			token->labels = ft_lstmap(lists->labels, ft_lstget);
			// append_linker_label(&lists->link_labels, token);
			// append_linker_refs(&lists->link_refs, token);
			// append_token(&lists->tokens, token);
			ft_lstdel(&lists->labels, ft_lstelemfree);
			// system("leaks asm");
			// break ;
			// ft_printf("FALSE: %s\n", file->line);
		}
	}
	// ft_lstiter(lists->labels, ft_lstprint);
}
