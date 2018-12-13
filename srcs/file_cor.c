#include "asm.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

const t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												4},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									4},
	{"st",		3,	{T_REG, T_IND | T_REG},									4},
	{"add",		4,	{T_REG, T_REG, T_REG},									4},
	{"sub",		5,	{T_REG, T_REG, T_REG},									4},	
	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"zjmp",	9,	{T_DIR},												2},
	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2},
	{"fork",	12,	{T_DIR},												2},
	{"lld",		13,	{T_DIR | T_IND, T_REG},									4},
	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"lfork",	15,	{T_DIR},												2},
	{"aff",		16,	{T_REG},												4},
	{0, 		0,	{0}}
};
static t_file_cor	*file_cor_new(void)
{
	return (ft_memalloc(sizeof(t_file_cor)));
}

void    			file_cor_del(t_file_cor **fc)
{
	ft_memdel((void**)&(*fc)->header);
	free((*fc)->name);
	// free((*fc)->bytecode);
	free(*fc);
}

// void	file_cor_write(t_file_cor file_cor, uint8_t flags)
// {
	// if (i->flags & FLAG_A)
	// 	ft_printf("Output a stripped and annotated version\n");
	// else
	// {
	// 	ft_printf("convert to byte-code\n");
	// 	// i->byte_code = convert_to_byte_code(i->compiled_data);
	// 	// write_cor_file(&i->file);
	// }
	// file_clear(&i->file);
// }

// void        file_cor_compile(t_file_cor *file_cor, t_file *file) // test version
// {
// 	// link_labels(stacks);
// 	// make_bytecode(stacks, file_cor);
// 	// ft_printf(".name: %s\n", file->hdr.prog_name);
// 	// ft_printf(".comment: %s\n", file->hdr.comment);
// 	// ft_printf("DATA: \n%s\n", file->data);
// 	file_cor = NULL;
// 	// free(lists);
// 	free(counter);
// }

uint8_t				instruction_get_code(char *instr)
{
	uint8_t	instr_code;
	ssize_t curr_instr;

	instr_code = 0;
	curr_instr = -1;
	while (++curr_instr < NUM_INSTRUCTIONS)
	{
		if (ft_strnequ(g_instrs_tab[curr_instr].name, instr, ft_strlen(instr)))
			instr_code = g_instrs_tab[curr_instr].instr_code;
	}
	if (instr_code == 0)
		semantic_errors(E_UNKNOWN_INSTR, instr, NULL);
	return (instr_code);
}

bool				is_register(const char *arg)
{
	char	*copy_arg;
	size_t	arg_len;

	copy_arg = (char *)arg;
	arg_len = ft_strlen(copy_arg);
	if (*copy_arg == 'r' && arg_len >= 1 && arg_len <= 3)
	{
		++copy_arg;
		while (*copy_arg)
		{
			if (!(ft_isdigit(*copy_arg)))
				return (false);
			copy_arg++;
		}
	}
	else
		return (false);
	return (true);
}

bool				is_direct(const char *arg)
{
	return (*arg == DIRECT_CHAR);
}

bool				is_indirect(const char *arg)
{
	if (!ft_strchr(LABEL_CHARS, *arg))
		lexical_errors(E_INVALID_SYMBOLS, (char*)arg, NULL);
	return (true);
}

uint8_t				argument_get_type(const char *arg)
{
	uint8_t	arg_type;

	arg_type = 0;
	if (is_register(arg))
		arg_type = REG_CODE;
	else if (is_direct(arg))
		arg_type = DIR_CODE;
	else if (is_indirect(arg))
		arg_type = IND_CODE;
	return (arg_type);
}

uint8_t				arguments_get_code(uint8_t instr_code, t_token *token)
{
	uint8_t	shift;
	uint8_t	arg_type;
	uint8_t	args_code;
	ssize_t	curr_arg;
	
	shift = 6;
	arg_type = 0;
	curr_arg = -1;
	args_code = 0;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (token->args[curr_arg])
		{
			arg_type = argument_get_type(token->args[curr_arg]);
			args_code = (args_code | (arg_type << shift));
			shift -= 2;
		}
	}
	return (args_code);
}

size_t				instruction_get_pos(t_bytecode *b_prevtoken)
{
	return (b_prevtoken ? b_prevtoken->pos + b_prevtoken->size : 0);
}

// size_t				instruction_get_size(t_bytecode *b_token)
// {

// }

void				arguments_convert_to_bytecode(t_bytecode *b_token, t_token *token)
{
	
}

t_bytecode			*token_convert_to_bytecode(t_bytecode *b_prevtoken, t_token *token)
{
    t_bytecode	*b_token;

	b_token = ft_memalloc(sizeof(t_bytecode));
    b_token->args_code = arguments_get_code(b_token->instr_code, token);
    arguments_convert_to_bytecode(b_token, token);
	printf(BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(b_token->args_code));

	b_token->instr_code = instruction_get_code(token->instr);
	// b_token->pos = instruction_get_pos(b_prevtoken);
    // b_token->size = instruction_get_size(b_token);

    // arguments_valid_code(b_token);

	// ssize_t	i = -1;

	// while (++i < MAX_ARGS_NUMBER - 1)
	// {

	// }

	// b_token->labels = ft_lstmap(token->labels, ft_lstget);
	// free(b_token);
    return (b_token);
}

void				append_bytecoded_tokens(t_list **b_tokens, t_bytecode *b_token)
{
	ft_lstaddend(b_tokens, ft_lstnew(b_token, sizeof(t_bytecode)));
	ft_memdel((void**)&b_token);
}

t_list				*tokens_convert_to_bytecode(t_list *tokens)
{
	t_list		*b_tokens;
	t_bytecode	*b_token;
	t_bytecode	*b_prevtoken;

	b_prevtoken = NULL;
	while (tokens)
	{
		b_token = token_convert_to_bytecode(b_prevtoken, (t_token *)tokens->content);
		// b_prevtoken = b_token;
		// append_bytecoded_tokens(&b_tokens, b_token);
		tokens = tokens->next;
	}
	return (b_tokens);
}

t_file_cor			*file_cor_make(t_file *f, t_counter *c) // test version
{
	t_file_cor		*fc;
	t_list			*tokens;
	t_list			*b_tokens;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	tokens = tokens_make(f, c);
	ft_lstiter(tokens, token_print);
	b_tokens = tokens_convert_to_bytecode(tokens);
	// link_references(b_tokens, tokens);

	// fc->memory = memory_new(b_tokens);
	// fc->memory->field = memory_get_field(fc, b_tokens);
	// ft_free_tocens(&tokens);
	tokens_del(&tokens);
	return (fc);
}
