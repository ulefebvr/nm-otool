#include <mach-o/loader.h>

#include "nm.h"
#include "swap.h"
#include "libft.h"

static t_lc				*get_lc(uint32_t magic, char *ptr)
{
	t_lc				*lc;

	lc = 0;
	if (magic == MH_MAGIC)
	{
		lc = (t_lc *)(ptr + sizeof(struct mach_header));
	}
	else if (magic == MH_MAGIC_64)
	{
		lc = (t_lc *)(ptr + sizeof(struct mach_header_64));
	}
	return (lc);
}

static t_symtab			*nm_load_macho_symtab_32(t_stc *symtab, t_ofile *ofile)
{
	uint32_t			i;
	char				*stringtable;
	struct nlist		*array;
	t_symtab			*head;
	t_symtab			*tail;

	i = 0;
	head = 0;
	tail = 0;
	array = (struct nlist *)((char *)ofile->ptr + symtab->symoff);
	stringtable = (char *)ofile->ptr + symtab->stroff;
	while (i < symtab->nsyms)
	{
		tail = add_new_stlist(tail, stringtable, array[i], ofile);
		if (head == 0)
			head = tail;
		++i;
	}
	return (head);
}

static t_symtab			*nm_load_macho_symtab_64(t_stc *symtab, t_ofile *ofile)
{
	uint32_t			i;
	char				*stringtable;
	struct nlist_64		*array;
	t_symtab			*head;
	t_symtab			*tail;

	i = 0;
	head = 0;
	tail = 0;
	array = (struct nlist_64 *)((char *)ofile->ptr + symtab->symoff);
	stringtable = (char *)ofile->ptr + symtab->stroff;
	while (i < symtab->nsyms)
	{
		tail = add_new_stlist_64(tail, stringtable, array[i], ofile);
		if (head == 0)
			head = tail;
		++i;
	}
	return (head);
}

static t_symtab			*nm_load_macho_symtab(
	uint32_t magic, t_stc *symtab, t_ofile *ofile)
{
	t_stc				symtab_cpy;

	ft_memcpy(&symtab_cpy, symtab, sizeof(t_stc));
	symtab_cpy.nsyms = swap_uint32_t(symtab_cpy.nsyms, ofile->swap);
	symtab_cpy.symoff = swap_uint32_t(symtab_cpy.symoff, ofile->swap);
	symtab_cpy.stroff = swap_uint32_t(symtab_cpy.stroff, ofile->swap);
	if (magic == MH_MAGIC)
	{
		return (nm_load_macho_symtab_32(&symtab_cpy, ofile));
	}
	return (nm_load_macho_symtab_64(&symtab_cpy, ofile));
}

t_symtab				*nm_load_macho_command(uint32_t magic, t_ofile *ofile)
{
	t_symtab			*stlist;
	uint32_t			i;
	uint32_t			ncmds;
	t_lc				*lc;

	i = 0;
	magic = swap_uint32_t(magic, ofile->swap);
	ofile->lc = get_lc(magic, ofile->ptr);
	lc = ofile->lc;
	ncmds = swap_uint32_t(((struct mach_header *)(ofile->ptr))->ncmds,\
	ofile->swap);
	while (i < ncmds && swap_uint32_t(lc->cmd, ofile->swap) != LC_SYMTAB)
	{
		lc = (t_lc *)((char *)lc + swap_uint32_t(lc->cmdsize, ofile->swap));
		++i;
	}
	if (i == ncmds)
	{
		stlist = 0;
	}
	else
	{
		if (swap_uint32_t(lc->cmd, ofile->swap) == LC_SYMTAB)
		stlist = nm_load_macho_symtab(magic, (t_stc *)lc, ofile);
	}
	return (stlist);
}
