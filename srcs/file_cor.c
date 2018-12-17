#include "asm.h"

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

void				link_references(t_list *b_tokens)
{
	ssize_t		curr_arg;
	t_list		*refs;
	t_list		*labels_in;
	t_list		*label_tmp;
	bool		found;
	// get ref
	//	find label with the same name
	//		if found
	// 			set value
	//		else
	//			error: no label with this name
	refs = b_tokens;
	while (refs)
	{
		found = false;
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if (((t_bytecode *)refs->content)->args[curr_arg]
			&& ((t_bytecode *)refs->content)->args[curr_arg]->ref.name)
			{
				labels_in = b_tokens;
				while (labels_in)
				{
					label_tmp = ((t_bytecode *)labels_in->content)->labels;
					while (label_tmp)
					{
						if (ft_strnequ(((t_bytecode *)refs->content)->args[curr_arg]->ref.name, ((t_label *)label_tmp->content)->name, ((t_label *)label_tmp->content)->len))
						{
							found = true;
							if (((t_bytecode *)refs->content)->args[curr_arg]->dir_size == USHORT)
								((t_bytecode *)refs->content)->args[curr_arg]->val16 = ((t_bytecode *)labels_in->content)->pos - ((t_bytecode *)refs->content)->pos;
							else if (((t_bytecode *)refs->content)->args[curr_arg]->dir_size == UINT)
								((t_bytecode *)refs->content)->args[curr_arg]->val32 = ((t_bytecode *)labels_in->content)->pos - ((t_bytecode *)refs->content)->pos;
						}
						label_tmp = label_tmp->next;
					}
					labels_in = labels_in->next;
				}
				if (!found)
				{
					if (((t_bytecode *)refs->content)->args[curr_arg]->code == DIR_CODE)
						printf("ERROR: UNKNWON REFERENCE: \"%c%c%s\"\n", DIRECT_CHAR, LABEL_CHAR, ((t_bytecode *)refs->content)->args[curr_arg]->ref.name);
					else if (((t_bytecode *)refs->content)->args[curr_arg]->code == IND_CODE)
						printf("ERROR: UNKNWON REFERENCE: \"%c%s\"\n", LABEL_CHAR,((t_bytecode *)refs->content)->args[curr_arg]->ref.name);
					exit(1);
				}
			}
		}
		refs = refs->next;
	}
}

t_file_cor			*file_cor_make(t_file *f, t_counter *c) // test version
{
	t_file_cor		*fc;
	t_list			*tokens;
	t_list			*b_tokens;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	tokens = tokens_make(f, c);
	b_tokens = tokens_tbc(tokens); /* tbc - to bytecode */
	link_references(b_tokens);
	ft_lstiter(tokens, token_print);
	ft_lstiter(b_tokens, b_token_print);

	// fc->memory = memory_new(b_tokens);
	// fc->memory->field = memory_get_field(fc, b_tokens);
	// ft_free_tocens(&tokens);
	tokens_del(&tokens);
	return (fc);
}
