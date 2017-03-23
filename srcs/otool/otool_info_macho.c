/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_info_macho.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:07 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:08 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

#include "libft.h"
#include "otool.h"
#include "misc.h"
#include "swap.h"

static t_lc		*get_lc(uint32_t magic, char *ptr)
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

static int		info_macho32(void *ptr, t_otool *otool, t_ofile *ofile)
{
	uint32_t	i;
	t_sc32		*segment;
	t_s32		*section;

	i = 0;
	segment = (t_sc32 *)ptr;
	if (segment->nsects == 0)
		return (0);
	section = (t_s32 *)((char *)segment + sizeof(t_sc32));
	if (ft_strcmp(section[i].segname, SEG_TEXT))
		return (0);
	otool->type = 32;
	while (i < swap_uint32_t(segment->nsects, ofile->swap))
	{
		if (!ft_strcmp(section[i].sectname, SECT_TEXT))
		{
			otool->section = (void *)(section + i);
			otool->section_content = (char *)ofile->ptr
				+ swap_uint32_t(section[i].offset, ofile->swap);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		info_macho64(void *ptr, t_otool *otool, t_ofile *ofile)
{
	uint32_t	i;
	t_sc64		*segment;
	t_s64		*section;

	i = 0;
	segment = (t_sc64 *)ptr;
	if (segment->nsects == 0)
		return (0);
	section = (t_s64 *)((char *)segment + sizeof(t_sc64));
	if (ft_strcmp(section[i].segname, SEG_TEXT))
		return (0);
	otool->type = 64;
	while (i < segment->nsects)
	{
		if (!ft_strcmp(section[i].sectname, SECT_TEXT))
		{
			otool->section = (void *)(section + i);
			otool->section_content = (char *)ofile->ptr + section[i].offset;
			return (1);
		}
		i++;
	}
	return (0);
}

int				otool_info_macho(uint32_t magic, t_otool *otool, t_ofile *ofile)
{
	t_lc		*lc;
	uint32_t	i;
	uint32_t	ncmds;

	i = 0;
	ofile->lc = get_lc(magic, ofile->ptr);
	ncmds = swap_uint32_t(((struct mach_header *)ofile->ptr)->ncmds, \
		ofile->swap);
	lc = ofile->lc;
	while (i < ncmds)
	{
		if (swap_uint32_t(lc->cmd, ofile->swap) == LC_SEGMENT
			&& info_macho32(lc, otool, ofile))
		{
			return (1);
		}
		else if (swap_uint32_t(lc->cmd, ofile->swap) == LC_SEGMENT_64
			&& info_macho64(lc, otool, ofile))
		{
			return (1);
		}
		lc = (t_lc *)((char *)lc + swap_uint32_t(lc->cmdsize, ofile->swap));
		i++;
	}
	return (0);
}
