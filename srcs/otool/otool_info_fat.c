/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_info_fat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:03 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:03 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	(void)otool;
	while (i < narchs)
	{
		if (swap_uint32_t(archs[i].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ptr + swap_uint32_t(archs[i].offset, swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			process_otool(ofile, 1);
			ofile->swap = swap;
			ofile->ptr = ptr;
			return (1);
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

	i = 0;
	(void)otool;
	while (i < narchs)
	{
		if (swap_uint32_t(archs[i].cputype, ofile->swap) == CPU_TYPE_X86_64)
		{
			ptr = ofile->ptr;
			swap = ofile->swap;
			ofile->ptr = (char *)ptr + swap_uint64_t(archs[i].offset, swap);
			misc_check_swap_need(*(uint32_t *)ofile->ptr, &ofile->swap);
			process_otool(ofile, 1);
			ofile->swap = swap;
			ofile->ptr = ptr;
			return (1);
		}
		i++;
	}
	return (0);
}

int				otool_info_fat(uint32_t magic, t_otool *otool, t_ofile *ofile)
{
	if (magic == FAT_MAGIC)
	{
		info_fat32(
			(t_arch32 *)(ofile->ptr + sizeof(t_fh)),
			swap_uint32_t(((t_fh *)ofile->ptr)->nfat_arch, ofile->swap),
			otool, ofile);
	}
	else
	{
		info_fat64(
			(t_arch64 *)(ofile->ptr + sizeof(t_fh)),
			((t_fh *)ofile->ptr)->nfat_arch,
			otool, ofile);
	}
	return (0);
}
