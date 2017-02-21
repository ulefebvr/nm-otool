#ifndef MISC_H
# define MISC_H

#include <stddef.h>
#include <stdint.h>

typedef
struct load_command		t_lc;

typedef struct			s_ofile
{
	char				*filename;
	size_t				filesize;
	void				*ptr;
	uint32_t			ncmds;
	t_lc				*lc;
	char				swap;
	int					filetype;
}						t_ofile;

void					misc_check_swap_need(uint32_t magic, char *swap);

int						misc_valid_magic(uint32_t magic);

int						misc_is_macho_file(uint32_t magic);
int						misc_is_fat(uint32_t magic);
void					misc_check_filetype(uint32_t magic, int *filetype);

#endif
