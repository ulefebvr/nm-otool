#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "otool.h"
#include "swap.h"
#include "misc.h"

static int		info_fat32(
	t_arch32 *archs, uint32_t narchs, t_otool *otool, t_ofile *ofile)
{
	uint32_t	i;
	void		*ptr;
	char		swap;
	uint32_t	magic;

	i = 0;
	while (i < narchs)
	{
		if (swap_uint32_t(archs[i].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ptr + swap_uint32_t(archs[i].offset, swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			magic = swap_uint32_t(*(uint32_t *)ofile->ptr, ofile->swap);
			i = otool_info_macho(magic, otool, ofile);
			ofile->swap = swap;
			ofile->ptr = ptr;
			return ((int)i);
		}
		i++;
	}
	return (0);
}

static int		info_fat64(
	t_arch64 *archs, uint32_t narchs, t_otool *otool, t_ofile *ofile)
{
	uint32_t	i;
	void		*ptr;
	char		swap;
	uint32_t	magic;

	i = 0;
	while (i < narchs)
	{
		if (swap_uint32_t(archs[i].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ptr + swap_uint64_t(archs[i].offset, swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			magic = swap_uint32_t(*(uint32_t *)ofile->ptr, ofile->swap);
			i = otool_info_macho(magic, otool, ofile);
			ofile->swap = swap;
			ofile->ptr = ptr;
			return ((int)i);
		}
		i++;
	}
	return (0);
}

int				otool_info_fat(uint32_t magic, t_otool *otool, t_ofile *ofile)
{
	if (magic == FAT_MAGIC)
	{
		return (info_fat32(
			(t_arch32 *)(ofile->ptr + sizeof(t_fh)),
			swap_uint32_t(((t_fh *)ofile->ptr)->nfat_arch, ofile->swap),
			otool, ofile));
	}
	else
	{
		return (info_fat64(
			(t_arch64 *)(ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch,
			otool, ofile));
	}
	return (0);
}
