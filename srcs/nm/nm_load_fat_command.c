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

static void				process_nm(t_ofile *ofile, int opt)
{
	t_symtab		*stlist;

	if ((stlist = nm_get_stlist(ofile, 0, opt | AR_T)))
	{
		stlist = nm_stlist_sort(stlist, opt | AR_T);
		nm_stlist_display(stlist, ofile, opt | AR_T);
		nm_stlist_free(stlist);
	}
}

t_symtab				*nm_get_fat_list32(
	t_arch32 *arch, uint32_t narchs, t_ofile *ofile, int opt)
{
	void				*ptr;
	char				swap;
	t_symtab			*stlist;

	stlist = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == HOST_CPU)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ofile->ptr
				+ swap_uint32_t(arch[narchs].offset, ofile->swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
			process_nm(ofile, opt);
			ofile->ptr = ptr;
			ofile->swap = swap;
			break ;
		}
	}
	return (stlist);
}

t_symtab				*nm_get_fat_list64(
	t_arch64 *arch, uint32_t narchs, t_ofile *ofile, int opt)
{
	void				*ptr;
	char				swap;
	t_symtab			*stlist;

	stlist = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == HOST_CPU)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ofile->ptr
				+ swap_uint64_t(arch[narchs].offset, ofile->swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			ofile->ncmds = ((struct mach_header *)ofile->ptr)->ncmds;
			process_nm(ofile, opt);
			ofile->ptr = ptr;
			ofile->swap = swap;
			break ;
		}
	}
	return (stlist);
}

t_symtab				*nm_load_fat_command(uint32_t magic, t_ofile *ofile,
							int opt)
{
	magic = swap_uint32_t(magic, ofile->swap);
	if (magic == FAT_MAGIC)
	{
		if (no_host_cputype32((t_arch32 *)((char *)ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch, ofile))
			show_all_cputype32((t_arch32 *)((char *)ofile->ptr + sizeof(t_fh)),
				((t_fh *)ofile->ptr)->nfat_arch, ofile), opt);
		else
			nm_get_fat_list32((t_arch32 *)((char *)ofile->ptr + sizeof(t_fh)),
				((t_fh *)ofile->ptr)->nfat_arch, ofile, opt);
	}
	else
	{
		if (no_host_cputype64((t_arch64 *)((char *)ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch, ofile))
			show_all_cputype64((t_arch64 *)((char *)ofile->ptr + sizeof(t_fh)),
				((t_fh *)ofile->ptr)->nfat_arch, ofile), opt);
		else
			nm_get_fat_list64((t_arch64 *)((char *)ofile->ptr + sizeof(t_fh)),
				((t_fh *)ofile->ptr)->nfat_arch, ofile, opt);
	}
	return (NULL);
}
