#include "asm.h"

static t_file_cor  *file_cor_new(void)
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

void    file_cor_del(t_file_cor **fc)
{
	ft_memdel(&(*fc)->header);
	free((*fc)->name);
	free((*fc)->bytecode);
	// free((*file)->line);
	free(*fc);
}

t_file_cor  *file_cor_make(t_file *f, t_counter *c) // test version
{
	t_file_cor	*fc;
	t_list		*tokens;

	fc = file_cor_new();
	fc->header = header_get(f->data, c);
	tokens = tokens_make(f, c);
	tokens_link(tokens);
	fc->bytecode = file_cor_make_bytecode(fc->header, tokens);
	// file_cor_compile(file_cor, file);
	return (fc);
}
