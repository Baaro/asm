#include "asm.h"

// const t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
// {
// 	{"live",	1,	{T_DIR},												4},
// 	{"ld",		2,	{T_DIR | T_IND, T_REG},									4},
// 	{"st",		3,	{T_REG, T_IND | T_REG},									4},
// 	{"add",		4,	{T_REG, T_REG, T_REG},									4},
// 	{"sub",		5,	{T_REG, T_REG, T_REG},									4},	
// 	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
// 	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
// 	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
// 	{"zjmp",	9,	{T_DIR},												2},
// 	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
// 	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2},
// 	{"fork",	12,	{T_DIR},												2},
// 	{"lld",		13,	{T_DIR | T_IND, T_REG},									4},
// 	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
// 	{"lfork",	15,	{T_DIR},												2},
// 	{"aff",		16,	{T_REG},												4},
// 	{0, 		0,	{0}}
// };

// void				append_bytecoded_tokens(t_list **b_tokens, t_bytecode *b_token)
// {
// 	ft_lstaddend(b_tokens, ft_lstnew(b_token, sizeof(t_bytecode)));
// 	ft_memdel((void**)&b_token);
// }

// t_bytecode			*token_tbc(t_bytecode *b_prevtoken, t_token *token)
// {
//     t_bytecode	*b_token;

// 	b_token = ft_memalloc(sizeof(t_bytecode));
// 	b_token->instr_code = instruction_get_code(token->instr);
//     arguments_set(b_token, token);
// 	arguments_valid(b_token);
// 	// b_token->pos = instruction_get_pos(b_prevtoken);
//     // b_token->size = instruction_get_size(b_token);
// 	// b_token->labels = ft_lstmap(token->labels, ft_lstget);
// 	// free(b_token);
//     return (b_token);
// }

// t_list				*tokens_tbc(t_list *tokens)
// {
// 	t_list		*b_tokens;
// 	t_bytecode	*b_token;
// 	t_bytecode	*b_prevtoken;

// 	b_prevtoken = NULL;
// 	while (tokens)
// 	{
// 		b_token = token_tbc(b_prevtoken, (t_token *)tokens->content);
// 		// b_prevtoken = b_token;
// 		// append_bytecoded_tokens(&b_tokens, b_token);
// 		tokens = tokens->next;
// 	}
// 	return (b_tokens);
// }
