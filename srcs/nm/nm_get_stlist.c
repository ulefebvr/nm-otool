#include <mach-o/loader.h>
#include <ar.h>

#include <string.h>

#include "nm.h"
#include "misc.h"
#include "swap.h"
#include "libft.h"

t_symtab			*nm_get_stlist(t_ofile *ofile)
{
	uint32_t		magic;
	t_symtab		*stlist;

	stlist = 0;
	magic = *(uint32_t *)ofile->ptr;
	misc_check_swap_need(magic, &(ofile->swap));
	misc_check_filetype(swap_uint32_t(magic, ofile->swap), &(ofile->filetype));
	if (misc_is_macho_file(magic))
	{
		ft_print("\033[31m%s\033[0m\n", "MACHO FILE");
		ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
		stlist = nm_load_macho_command(magic, ofile);
	}
	else if (misc_is_fat(magic))
	{
		ft_print("\033[31m%s\033[0m\n", "FAT FILE");
		stlist = nm_load_fat_command(magic, ofile);
	}
	else if (!strncmp(ofile->ptr, ARMAG, SARMAG))
	{
		ft_print("\033[31m%s\033[0m\n", "ARCHIVE");
	}
	else
	{
		ft_fdprint(2, "%s\n", "Unrecognized file format");
	}
	return (stlist);
}
