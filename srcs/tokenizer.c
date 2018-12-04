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

// size_t			valid_line(char *line)
// {
// 	size_t	counter;
// 	size_t	len;

// 	counter = -1;
// 	len = ft_strlen(line);
// 	while (++counter < len)
// 	{
// 		if (!(ft_strchr(INSTR_CHARS, line[counter])))
// 			break ;
// 	}
// 	return (counter);
// }

bool			is_valid_symbols(char *line, size_t len, t_counter *counter)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
		{
			counter->column += i + 1;
			lexical_errors(E_INVALID_SYMBOLS, line, counter);
		}
	}
	return (i == len);
}

// bool			instr_exists(char *line)
// {
// 	return (ft_strcspn(line, DELIMS_CHARS) != 0);
// }

bool			is_label(char *label, t_counter *counter)
{
	size_t	label_len;

	label_len = ft_strlen(label);
	if (ft_strcspn(label, ":") + 1 == label_len)
		return (is_valid_symbols(label, label_len - 1, counter));
	return (false);
}

// char			*get_label(char *line, bool is_solo, t_counter *counter)
// {
// 	char *pos;
	
// 	if ((pos = ft_strchr(line, LABEL_CHAR)))
// 	{
// 		if (is_valid_symbols(line, pos - line, counter))
// 			return (ft_strsub(line, 0, pos - line));
// 	}
// 	return (NULL);
	
// }

char			*get_label(char *line, bool is_solo, t_counter *counter)
{
	size_t	lab_char_pos;
	char	*label;

	label = NULL;
	lab_char_pos = ft_strcspn(line, ":");
	if (line[lab_char_pos] == LABEL_CHAR
	&& is_valid_symbols(line, lab_char_pos, counter))
	{
		if (is_solo)
		{
			if (lab_char_pos + 1 == ft_strlen(line))
				label = ft_strsub(line, 0, lab_char_pos);
			else
				label = NULL;
		}
		else
		{
			is_valid_symbols(line + lab_char_pos + 1, ft_strlen(line + lab_char_pos + 1), counter);
			label = ft_strsub(line, 0, lab_char_pos);
		}
	}
	return (label);
}

//	[+]	get_label()
//	[-]	get_instruction()
// 	[-]	get_arguments()

void			token_print(t_token *token)
{
	printf("\n-----------TOKEN-----------\n");
	printf("LABELS:\n");
	ft_lstiter(token->labels, ft_lstprint);
	printf("INSTRUCTION: [%s]\n", token->instr);
	printf("ARGUMENTS:\n");
	int i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		printf("arg[%d] -> %s\n", i, token->args[i]);
	printf("\n-----------TOKEN-----------\n");
}

t_token 		*new_token(t_list *labels, char *line, t_counter *counter)
{
	t_token		*token;

	token = ft_memalloc(sizeof(t_token));
	if ((token->label = get_label(ft_strtok(line, ":"), 0, counter))) // label with instr
	{
		append_label(&labels, token->label);
		token->instr = ft_strdup(ft_strtok(NULL, DELIMS_CHARS));
		printf("INSTR: %s\n", token->instr);
	}
	else // instr without label
		token->instr = ft_strdup(ft_strtok(line, DELIMS_CHARS));
	token->labels = ft_lstmap(labels, ft_lstget);
	// get arguemnts();
	int i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		token->args[i] = ft_strtrim(ft_strtok(NULL, ","));
	return (token);
}

void			tmp_token_clear(t_tmp_token *token)
{
	// if (token->label)
		// free(token->label);
	// if (token->instr)
		// free(token->instr);
}

void			tokenizer(t_file *file, t_lists *lists, t_counter *counter) // test version
{
	t_token		*token;
	char 		*tmp;

	tmp = NULL;
	while (file_get_line(file, counter) == 1)
	{
		if ((tmp = get_label(file->line, 1, counter)))
		{
			printf("iF line: %s\n", file->line);
			append_label(&lists->labels, tmp);
		}
		else
		{
			printf("eLSE line: %s\n", file->line);
			token = new_token(lists->labels, file->line, counter);
			token_print(token);
			// tmp_token_clear(&token);
			// append_linker_label(&lists->link_labels, token);
			// append_linker_refs(&lists->link_refs, token);
			// append_token(&lists->tokens, token);
		}
	}
}
// if we found ':' at the end of the string -> it's the solo label
// else if we did not ->
					// if we found ':' -> cut and valid label
					// else if we did not cut and valid instruction 