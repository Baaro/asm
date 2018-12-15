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

t_file_cor			*file_cor_make(t_file *f, t_counter *c) // test version
{
	t_file_cor		*fc;
	t_list			*tokens;
	t_list			*b_tokens;

	fc = file_cor_new();
	fc->header = header_get(f, c);
	tokens = tokens_make(f, c);
	ft_lstiter(tokens, token_print);
	// b_tokens = tokens_tbc(tokens); /* tbc - to bytecode */
	// link_references(b_tokens, tokens);

	// fc->memory = memory_new(b_tokens);
	// fc->memory->field = memory_get_field(fc, b_tokens);
	// ft_free_tocens(&tokens);
	tokens_del(&tokens);
	return (fc);
}
