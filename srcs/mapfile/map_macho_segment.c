/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_macho_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:28:22 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 11:28:24 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"
#include "swap.h"

#include "libft.h"

t_mapfile		*map_check_segment32(t_mapfile *map, t_sc32 *segment)
{
	uint32_t	i;
	uint32_t	nsects;
	t_s32		*sections;

	i = 0;
	nsects = swap_uint32_t(segment->nsects, map->macho_swap);
	if (map->file_size
		< ((char *)segment - (char *)map->file_addr) + sizeof(t_sc32))
	{
		ft_fdprint(2, "Problem file %s, check segments\n", map->file_name);
		return (map_release(map));
	}
	sections = (t_s32 *)((char *)segment + sizeof(t_sc32));
	while (i < nsects)
	{
		map_add_section(map, sections, i, nsects);
		if (map->file_size
			< swap_uint32_t(sections[i].offset, map->macho_swap)
			+ swap_uint32_t(sections[i].size, map->macho_swap))
			return (map_release(map));
		i++;
	}
	return (map);
}

t_mapfile		*map_check_segment64(t_mapfile *map, t_sc64 *segment)
{
	uint32_t	i;
	uint32_t	nsects;
	t_s64		*sections;

	i = 0;
	nsects = swap_uint32_t(segment->nsects, map->macho_swap);
	if (map->file_size
		< ((char *)segment - (char *)map->file_addr) + sizeof(t_sc64))
	{
		ft_fdprint(2, "Problem file %s, check segments\n", map->file_name);
		return (map_release(map));
	}
	sections = (t_s64 *)((char *)segment + sizeof(t_sc64));
	while (i < nsects)
	{
		map_add_section(map, sections, i, nsects);
		if (map->file_size
			< swap_uint32_t(sections[i].offset, map->macho_swap)
			+ swap_uint32_t(sections[i].size, map->macho_swap))
			return (map_release(map));
		i++;
	}
	return (map);
}

t_mapfile		*map_check_segments(t_mapfile *map, t_lc *lc_segment)
{
	map->macho_segment = lc_segment;
	if (lc_segment->cmd == LC_SEGMENT)
	{
		if (map->file_size >= ((char *)lc_segment - (char *)map->file_addr)
			+ sizeof(t_sc32))
			return (map_check_segment32(map, (t_sc32 *)lc_segment));
	}
	else if (lc_segment->cmd == LC_SEGMENT_64)
	{
		if (map->file_size >= ((char *)lc_segment - (char *)map->file_addr)
			+ sizeof(t_sc64))
			return (map_check_segment64(map, (t_sc64 *)lc_segment));
	}
	return (map_release(map));
}
