
// #include "asm.h"

// void				insert_adresses(t_list **b_tokens, uint32_t *size)
// {
// 	ssize_t		curr_arg;
// 	t_list		*refs;
// 	t_list		*labels_in;
// 	t_list		*label_tmp;
// 	bool		found;

// 	// get ref
// 	//	find label with the same name
// 	//		if found
// 	// 			set value
// 	//		else
// 	//			error: no label with this name
// 	refs = *b_tokens;
// 	while (refs)
// 	{
// 		found = false;
// 		curr_arg = -1;
// 		while (++curr_arg < MAX_ARGS_NUMBER - 1)
// 		{
// 			get_adresses(label_tmp);
// 			if (((t_b_token *)refs->content)->args[curr_arg]
// 			&& ((t_b_token *)refs->content)->args[curr_arg]->ref)
// 			{
// 				labels_in = *b_tokens;
// 				while (labels_in)
// 				{
// 					label_tmp = ((t_b_token *)labels_in->content)->labels;
// 					while (label_tmp)
// 					{
// 						if (ft_strequ(((t_b_token *)refs->content)->args[curr_arg]->ref->name, ((t_label *)label_tmp->content)->name))
// 						{
// 							found = true;
// 							if (((t_b_token *)refs->content)->args[curr_arg]->code == IND_CODE)
// 								((t_b_token *)refs->content)->args[curr_arg]->ind = swap_uint16(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
// 							else if (((t_b_token *)refs->content)->args[curr_arg]->code == DIR_CODE)
// 							{
// 								if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == USHORT)
// 									((t_b_token *)refs->content)->args[curr_arg]->dir16 = swap_uint16(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
// 								else if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == UINT)
// 									((t_b_token *)refs->content)->args[curr_arg]->dir32 = swap_uint32(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
// 							}
// 						}
// 						label_tmp = label_tmp->next;
// 					}
// 					labels_in = labels_in->next;
// 				}
// 				if (!found)
// 				{
// 					if (((t_b_token *)refs->content)->args[curr_arg]->code == DIR_CODE)
// 						printf("ERROR: UNKNWON REFERENCE: \"%c%c%s\"\n", DIRECT_CHAR, LABEL_CHAR, ((t_b_token *)refs->content)->args[curr_arg]->ref->name);
// 					else if (((t_b_token *)refs->content)->args[curr_arg]->code == IND_CODE)
// 						printf("ERROR: UNKNWON REFERENCE: \"%c%s\"\n", LABEL_CHAR, ((t_b_token *)refs->content)->args[curr_arg]->ref->name);
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 		}
// 		*size += ((t_b_token*)refs->content)->size;
// 		refs = refs->next;
// 	}
// }