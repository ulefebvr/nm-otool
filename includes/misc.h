#ifndef MISC_H
# define MISC_H

#include <stddef.h>
#include <stdint.h>

#include <ar.h>

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

typedef struct			s_archive
{
	struct ar_hdr		*header;
	char				*member_name;
	uint32_t			offset;
	uint64_t			size;
	uint32_t			nranlib;
	void				*object;
	void				*ranlibs;
}						t_archive;

#define S_AR_HDR		(sizeof(struct ar_hdr))

void					misc_check_swap_need(uint32_t magic, char *swap);

int						misc_valid_magic(uint32_t magic);

int						misc_is_macho_file(uint32_t magic);
int						misc_is_fat(uint32_t magic);
void					misc_check_filetype(uint32_t magic, int *filetype);

t_archive				*get_ar_header(void *ptr, uint32_t offset, size_t size);
void					sort(t_archive **ar, uint32_t *size);
char					*get_membername(t_ofile *ofile);

#endif
