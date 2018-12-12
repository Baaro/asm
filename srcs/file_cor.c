#include "asm.h"

static t_file_cor	*file_cor_new(void)
{
	return (ft_memalloc(sizeof(t_file_cor)));
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

void    			file_cor_del(t_file_cor **fc)
{
	ft_memdel((void**)&(*fc)->header);
	free((*fc)->name);
	free((*fc)->bytecode);
	free(*fc);
}

// void	valid_instruction()
// {

// }

// void	valid_arguments()
// {

// }

t_bytecode			*token_convert_to_bytecode(t_bytecode *prev_elem, t_token *token)
{
    t_bytecode	*elem;

    elem = ft_memalloc(sizeof(t_bytecode));

    elem->instr_code = instruction_get_code(token);
    elem->pos = instruction_get_pos(prev_elem);
    elem->size = instruction_get_size(elem);

    elem->args_code = agruments_get_code(elem, token);
    arguments_valid_code(elem);

	ssize_t	i = -1;

	while (++i < MAX_ARGS_NUMBER - 1)
	{

	}

    arguments_convert_to_bytecode(elem, token);
	elem->labels = ft_lstmap(token->labels, ft_lstget);
    return (elem);
}

t_list				*tokens_convert_to_bytecode(t_list *tokens)
{
	t_list		*bytecoded_tokens;
	t_bytecode	*b_token;


}

t_file_cor			*file_cor_make(t_file *f, t_counter *c) // test version
{
	t_file_cor		*fc;
	t_memory		*m;
	t_list			*tokens;
	t_list			*bytecoded_tokens;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	ft_lstiter(tokens, token_print);

	tokens = tokens_make(f, c);
	bytecoded_tokens = tokens_convert_to_bytecode(tokens);
	link_references(bytecoded_tokens, tokens);

	m = memory_new(bytecoded_tokens);
	m->field = memory_get_field(m, bytecoded_tokens);
	return (fc);
}
