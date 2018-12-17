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

size_t		get_currunet_column(t_counter *counter)
{
	return (counter->column + counter->begin_whitespaces); 
}

size_t		get_currunet_position(t_counter *counter)
{
	return (counter->column);
}

bool	is_whitespaces(const char c)
{
	return (c == '\t' || c == ' ');
}

void			ft_lstprint(t_list *elem)
{
	if (elem)
	{
		printf("%s\n", ((t_label *)elem->content)->name);
	}
}

bool				is_valid_val(char *arg_str)
{
	if (*arg_str == '-')
		arg_str++;
	while (ft_isdigit(*arg_str))
	{
		if (*(arg_str + 1) == '\0')	
			return (true);
		arg_str++;
	}
	return (false);
}

void			token_print(t_list *token)
{
	ssize_t i;

	printf("\n-----------TOKEN-----------\n");
	printf("LABELS:\n");
	ft_lstiter(((t_token *)token->content)->labels, ft_lstprint);
	printf("INSTRUCTION: [%s]\n", ((t_token *)token->content)->instr);
	printf("ARGUMENTS:\n");
	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		printf("arg[%zu] -> %s\n", i, (*(t_token*)token->content).args[i]);
	printf("\n-----------TOKEN-----------\n");
}

void			b_token_print(t_list *b_token)
{
	ssize_t i;

	printf("\n-----------B-TOKEN-----------\n");
	printf("INSTR_CODE: ");
	printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(((t_bytecode *)b_token->content)->instr_code));
	printf("\nARGS_CODE: ");
	printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(((t_bytecode *)b_token->content)->args_code));
	printf("\nARGUMENTS:\n");
	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
	{
		if (((t_bytecode*)b_token->content)->args[i])
		{
			if (((t_bytecode*)b_token->content)->args[i]->code == REG_CODE
			|| ((t_bytecode*)b_token->content)->args[i]->code == IND_CODE
			|| ((t_bytecode*)b_token->content)->args[i]->dir_size == USHORT)
				printf("args[%zd] -> code:[%hhu] val:[%d]\n", i, ((t_bytecode*)b_token->content)->args[i]->code, ((t_bytecode*)b_token->content)->args[i]->val16);
			else if (((t_bytecode*)b_token->content)->args[i]->dir_size == UINT)
				printf("args[%zd] -> code:[%hhu] val:[%u]\n", i, ((t_bytecode*)b_token->content)->args[i]->code, ((t_bytecode*)b_token->content)->args[i]->val32);
		}
	}
	printf("\n-----------B-TOKEN-----------\n");
}

ssize_t			get_invalid_symbols(char *line, size_t len, char *valid_symbols)
{
	ssize_t	i;

	i = -1;
	while (line[++i] && i < (ssize_t)len)
	{
		if (!ft_strchr(valid_symbols, line[i]))
			return(i);
	}
	return (i == len ? -1 : i);
}


