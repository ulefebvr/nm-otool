/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_load_fat_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:22:13 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:22:14 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "nm.h"
#include "swap.h"
#include "libft.h"
#include "swap.h"
#include "misc.h"

t_symtab				*nm_get_fat_list32(
	t_arch32 *arch, uint32_t narchs, t_ofile *ofile)
{
	void				*ptr;
	char				swap;
	t_symtab			*stlist;

	stlist = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ofile->ptr
				+ swap_uint32_t(arch[narchs].offset, ofile->swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
			stlist = nm_load_macho_command(*(uint32_t *)ofile->ptr, ofile);
			ofile->ptr = ptr;
			ofile->swap = swap;
			break ;
		}
	}
	return (stlist);
}

t_symtab				*nm_get_fat_list64(
	t_arch64 *arch, uint32_t narchs, t_ofile *ofile)
{
	void				*ptr;
	char				swap;
	t_symtab			*stlist;

	stlist = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ofile->ptr
				+ swap_uint64_t(arch[narchs].offset, ofile->swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
			stlist = nm_load_macho_command(*(uint32_t *)ofile->ptr, ofile);
			ofile->ptr = ptr;
			ofile->swap = swap;
			break ;
		}
	}
	return (stlist);
}

t_symtab				*nm_load_fat_command(uint32_t magic, t_ofile *ofile)
{
	t_symtab			*stlist;

	stlist = 0;
	magic = swap_uint32_t(magic, ofile->swap);
	if (magic == FAT_MAGIC)
	{
		stlist = nm_get_fat_list32(
			(t_arch32 *)((char *)ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch, ofile);
	}
	else
	{
		stlist = nm_get_fat_list64(
			(t_arch64 *)((char *)ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch, ofile);
	}
	return (stlist);
}
