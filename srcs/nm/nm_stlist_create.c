#include <mach-o/nlist.h>
#include <mach-o/loader.h>

#include "nm.h"
#include "swap.h"
#include "libft.h"

static char			*get_the_corresponding_section_64(
	t_ofile *ofile, uint8_t n_sect)
{
	uint32_t			i;
	uint32_t			ncmds;
	t_lc				*tmp_lc;
	struct section_64	*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = ofile->lc;
	n_sect -= 1;
	while (ncmds < ofile->ncmds)
	{
		if (tmp_lc->cmd == LC_SEGMENT_64)
		{
			tmp_sect = (struct section_64 *)((char *)tmp_lc
				+ sizeof(struct segment_command_64));
			if (n_sect < i + ((struct segment_command_64 *)tmp_lc)->nsects)
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += ((struct segment_command_64 *)tmp_lc)->nsects;
		}
		tmp_lc = (t_lc *)((char *)tmp_lc + tmp_lc->cmdsize);
		++ncmds;
	}
	return (0);
}

static char			*get_the_corresponding_section_32(
	t_ofile *ofile, uint8_t n_sect)
{
	uint32_t			i;
	uint32_t			ncmds;
	t_lc				*tmp_lc;
	struct section		*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = ofile->lc;
	n_sect -= 1;
	while (ncmds < ofile->ncmds)
	{
		if (tmp_lc->cmd == LC_SEGMENT)
		{
			tmp_sect = (struct section *)((char *)tmp_lc
				+ sizeof(struct segment_command));
			if (n_sect < i + ((struct segment_command *)tmp_lc)->nsects)
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += ((struct segment_command *)tmp_lc)->nsects;
		}
		tmp_lc = (t_lc *)((char *)tmp_lc + tmp_lc->cmdsize);
		++ncmds;
	}
	return (0);
}

static char			get_type_letter(
	t_ofile *ofile, uint8_t n_type, uint64_t n_value, uint8_t n_sect)
{
	char			type;
	char			*section_name;

	type = 0;
	if ((n_type & N_TYPE) == N_INDR)
		type = 'I';
	else if ((n_type & N_TYPE) == N_STAB)
		type = '-';
	else if ((n_type & N_TYPE) == N_UNDF && (n_type & N_EXT) && n_value != 0)
		type = 'C';
	else if ((n_type & N_TYPE) == N_UNDF)
	{
		type = ((n_type & N_TYPE) == N_PBUD) ? 'u' : 'U';

	}
	else if ((n_type & N_TYPE) == N_ABS)
		type = 'A';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		section_name = (ofile->filetype == 8) ? 
			get_the_corresponding_section_32(ofile, n_sect) :
			get_the_corresponding_section_64(ofile, n_sect) ;
		if (section_name && !ft_strcmp(section_name, SECT_TEXT))
			type = 'T';
		else if (section_name && !ft_strcmp(section_name, SECT_DATA))
			type = 'D';
		else if (section_name && !ft_strcmp(section_name, SECT_BSS))
			type = 'B';
		else
			type = 'S';
	}
	return (!(n_type & N_EXT) ? ft_tolower(type) : type);
}

t_symtab			*add_new_stlist(
	t_symtab *tail, char *stringtable, struct nlist info, t_ofile *ofile)
{
	t_symtab		*node;

	node = ft_memalloc(sizeof(t_symtab));
	if (tail)
		tail->next = node;
	node->n_strx = swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->value = swap_uint32_t(info.n_value, ofile->swap);
	node->type = get_type_letter(ofile, info.n_type,
		(uint64_t)swap_uint32_t(info.n_value, ofile->swap), info.n_sect);
	node->name = stringtable + swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->n_sect = info.n_sect;
	// node->pathname; TO FOUND WHERE IT IS STORED
	return (node);
}

t_symtab			*add_new_stlist_64(
	t_symtab *tail, char *stringtable, struct nlist_64 info, t_ofile *ofile)
{
	t_symtab		*node;

	node = ft_memalloc(sizeof(t_symtab));
	if (tail)
		tail->next = node;
	node->n_strx = swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->value = swap_uint64_t(info.n_value, ofile->swap);
	node->type = get_type_letter(ofile, info.n_type,
		swap_uint64_t(info.n_value, ofile->swap), info.n_sect);
	node->name = stringtable + swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->n_sect = info.n_sect;
	// node->pathname; TO FOUND WHERE IT IS STORED
	return (node);
}

