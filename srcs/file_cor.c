#include "asm.h"

void				insert_adresses(t_list **b_tokens, uint32_t *size)
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
	refs = *b_tokens;
	while (refs)
	{
		found = false;
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)refs->content)->args[curr_arg]
			&& ((t_b_token *)refs->content)->args[curr_arg]->ref)
			{
				labels_in = *b_tokens;
				while (labels_in)
				{
					label_tmp = ((t_b_token *)labels_in->content)->labels;
					while (label_tmp)
					{
						if (ft_strequ(((t_b_token *)refs->content)->args[curr_arg]->ref->name, ((t_label *)label_tmp->content)->name))
						{
							found = true;
							if (((t_b_token *)refs->content)->args[curr_arg]->code == IND_CODE)
							{
								((t_b_token *)refs->content)->args[curr_arg]->ind = swap_uint16(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
							}
							else if (((t_b_token *)refs->content)->args[curr_arg]->code == DIR_CODE)
							{
								if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == USHORT)
									((t_b_token *)refs->content)->args[curr_arg]->dir16 = swap_uint16(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
								else if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == UINT)
									((t_b_token *)refs->content)->args[curr_arg]->dir32 = swap_uint32(((t_b_token *)labels_in->content)->pos - ((t_b_token *)refs->content)->pos);
							}
						}
						label_tmp = label_tmp->next;
					}
					labels_in = labels_in->next;
				}
				if (!found)
				{
					if (((t_b_token *)refs->content)->args[curr_arg]->code == DIR_CODE)
						printf("ERROR: UNKNWON REFERENCE: \"%c%c%s\"\n", DIRECT_CHAR, LABEL_CHAR, ((t_b_token *)refs->content)->args[curr_arg]->ref->name);
					else if (((t_b_token *)refs->content)->args[curr_arg]->code == IND_CODE)
						printf("ERROR: UNKNWON REFERENCE: \"%c%s\"\n", LABEL_CHAR, ((t_b_token *)refs->content)->args[curr_arg]->ref->name);
					exit(1);
				}
			}
		}
		*size += ((t_b_token*)refs->content)->size;
		refs = refs->next;
	}
}

static t_file_cor	*file_cor_new(void)
{
	return (ft_memalloc(sizeof(t_file_cor)));
}

void    			file_cor_del(t_file_cor **fc)
{
	ft_memdel((void**)&(*fc)->header);
	tokens_del(&(*fc)->tokens);
	b_tokens_del(&(*fc)->b_tokens);
	free((*fc)->name);
	free(*fc);
}

void				file_cor_write(t_file_cor *fc, uint8_t flags, t_counter *c)
{
	ssize_t curr_arg;

	write(fc->fd, &fc->header->magic, sizeof(fc->header->magic));
	write(fc->fd, &fc->header->prog_name, PROG_NAME_LENGTH + 4);
	fc->size = swap_uint32(fc->size);
	write(fc->fd, &fc->size, sizeof(uint32_t));
	write(fc->fd, &fc->header->comment, COMMENT_LENGTH + 4);
	t_list *b_tokens = fc->b_tokens;
	while (b_tokens)
	{
		if (((t_b_token *)b_tokens->content)->op_code)
			write(fc->fd, &((t_b_token *)b_tokens->content)->op_code, sizeof(uint8_t));
		if (((t_b_token *)b_tokens->content)->args_code)
			write(fc->fd, &((t_b_token *)b_tokens->content)->args_code, sizeof(uint8_t));
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)b_tokens->content)->args[curr_arg])
			{
				if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == REG_CODE)
					write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->reg, sizeof(uint8_t));
				else if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == DIR_CODE)
				{
					if (((t_b_token *)b_tokens->content)->args[curr_arg]->dir_size == USHORT)
						write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->dir16, sizeof(uint16_t));
					else if (((t_b_token *)b_tokens->content)->args[curr_arg]->dir_size == UINT)
						write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->dir32, sizeof(uint32_t));
				}
				else if (((t_b_token *)b_tokens->content)->args[curr_arg]->code == IND_CODE)
					write(fc->fd, &((t_b_token *)b_tokens->content)->args[curr_arg]->ind, sizeof(uint16_t));
			}
		}
		b_tokens = b_tokens->next;
	}
}

char				*file_cor_get_name(char *f_name)
{
	char	*slash;
	char	*dot;
	char	*fc_name;

	slash = ft_strrchr(f_name, '/');
	dot = ft_strchr(slash, '.');
	fc_name = ft_strsub(slash + 1, 0, dot - slash);
	fc_name = ft_strjoincl(fc_name, "cor", 0);
	return (fc_name);
}

t_file_cor			*file_cor_make(t_file *f, t_counter *c)
{
	t_file_cor	*fc;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	fc->tokens = tokens_make(f, c);
	fc->b_tokens = b_tokens_make(fc->tokens);
	insert_adresses(&fc->b_tokens, &fc->size);
	fc->name = file_cor_get_name(f->name);
	fc->modes = O_RDWR | O_TRUNC | O_CREAT;
	fc->permissions = S_IWUSR | S_IRUSR;
	fc->fd = open(fc->name, fc->modes, fc->permissions);

	// ft_lstiter(fc->tokens, token_print);
	// ft_lstiter(fc->b_tokens, b_token_print);
	return (fc);
}
