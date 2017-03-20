/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_macho_sections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:28:30 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 11:28:31 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"
#include "swap.h"

#include "libft.h"

void			add_section32(
	t_mapfile *map, t_s64 *macho_sections, t_s32 *section, uint32_t i)
{
	ft_memcpy(macho_sections[i].sectname, section[i].sectname, 16);
	ft_memcpy(macho_sections[i].segname, section[i].segname, 16);
	macho_sections[i].addr =
		(uint64_t)swap_uint32_t(section[i].addr, map->macho_swap);
	macho_sections[i].size =
		(uint64_t)swap_uint32_t(section[i].size, map->macho_swap);
	macho_sections[i].offset =
		swap_uint32_t(section[i].offset, map->macho_swap);
	macho_sections[i].align =
		swap_uint32_t(section[i].align, map->macho_swap);
	macho_sections[i].reloff =
		swap_uint32_t(section[i].reloff, map->macho_swap);
	macho_sections[i].nreloc =
		swap_uint32_t(section[i].nreloc, map->macho_swap);
	macho_sections[i].flags =
		swap_uint32_t(section[i].flags, map->macho_swap);
}

void			add_section64(
	t_mapfile *map, t_s64 *macho_sections, t_s64 *section, uint32_t i)
{
	ft_memcpy(macho_sections[i].sectname, section[i].sectname, 16);
	ft_memcpy(macho_sections[i].segname, section[i].segname, 16);
	macho_sections[i].addr =
		swap_uint64_t(section[i].addr, map->macho_swap);
	macho_sections[i].size =
		swap_uint64_t(section[i].size, map->macho_swap);
	macho_sections[i].offset =
		swap_uint32_t(section[i].offset, map->macho_swap);
	macho_sections[i].align =
		swap_uint32_t(section[i].align, map->macho_swap);
	macho_sections[i].reloff =
		swap_uint32_t(section[i].reloff, map->macho_swap);
	macho_sections[i].nreloc =
		swap_uint32_t(section[i].nreloc, map->macho_swap);
	macho_sections[i].flags =
		swap_uint32_t(section[i].flags, map->macho_swap);
}

t_mapfile		*map_add_section(
	t_mapfile *map, void *section, uint32_t i, uint32_t nsects)
{
	if (i == 0 && !map->macho_sections)
	{
		if (!(map->macho_sections = ft_memalloc(sizeof(t_s64) * nsects)))
			return (map_release(map));
	}
	if (map->macho_subtype == B32)
	{
		add_section32(map, map->macho_sections, (t_s32 *)section, i);
	}
	else
	{
		add_section64(map, map->macho_sections, (t_s64 *)section, i);
	}
	return (map);
}
