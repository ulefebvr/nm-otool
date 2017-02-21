#include <mach-o/loader.h>

#include "nm.h"
#include "misc.h"
#include "swap.h"

t_symtab			*nm_get_stlist(t_ofile *ofile)
{
	uint32_t		magic;
	t_symtab		*stlist;

	magic = *(uint32_t *)ofile->ptr;
	if (!misc_valid_magic(magic))
	{
		// ERR ?
		return ((t_symtab *)-1);
	}
	misc_check_swap_need(magic, &(ofile->swap));
	misc_check_filetype(swap_uint32_t(magic, ofile->swap), &(ofile->filetype));
	if (misc_is_macho_file(magic))
	{
		ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
		stlist = nm_load_macho_command(magic, ofile);
	}
	// else if (misc_is_fat(magic))
	// 	stlist = nm_load_fat_command(magic, ofile);
	else
	{
		;
	}
	return (stlist);
}
