/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_macho_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:20:57 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:14 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "mapfile.h"
#include "swap.h"
#include "libft.h"

t_subtype		get_macho_subtype(t_mapfile *map)
{
	if (map->magic == MH_MAGIC || map->magic == MH_CIGAM)
	{
		map->macho_swap = (map->magic == MH_CIGAM);
		map->magic = swap_uint32_t(map->magic, map->macho_swap);
		map->macho_subtype = B32;
		return (B32);
	}
	else if (map->magic == MH_MAGIC_64 || map->magic == MH_CIGAM_64)
	{
		map->macho_swap = (map->magic == MH_CIGAM_64);
		map->magic = swap_uint32_t(map->magic, map->macho_swap);
		map->macho_subtype = B64;
		return (B64);
	}
	return (0);
}

t_mapfile		*map_macho_getheader(t_mapfile *map)
{
	get_macho_subtype(map);
	if (map->macho_subtype == B32 || map->macho_subtype == B64)
	{
		if (map->file_size < sizeof(struct mach_header)
			+ sizeof(uint32_t) * (map->macho_subtype == B64))
		{
			ft_fdprint(2, "File %s is corrupted (no macho header)\n",
				map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->macho_header, map->file_addr, sizeof(t_mh));
		map->macho_header.magic = map->magic;
		map->macho_header.ncmds =
			swap_uint32_t(map->macho_header.ncmds, map->macho_swap);
		map->macho_header.sizeofcmds =
			swap_uint32_t(map->macho_header.sizeofcmds, map->macho_swap);
	}
	else
	{
		ft_fdprint(2, "Internal error on file %s, not recognized\n");
		return (map_release(map));
	}
	return (map);
}

t_mapfile		*map_macho_getlc(t_mapfile *map)
{
	size_t		size_struct;

	size_struct = sizeof(t_mh)
		+ ((map->macho_subtype == B64) * sizeof(uint32_t));
	if (map->file_size >= size_struct + map->macho_header.sizeofcmds)
	{
		map->macho_lc = (t_lc *)((char *)map->file_addr + size_struct);
	}
	else
	{
		ft_fdprint(2, "File %s is corrupted (no macho header)\n",
			map->file_name);
		return (map_release(map));
	}
	return (map);
}

t_mapfile		*map_macho_checklc(t_mapfile *map)
{
	t_lc		*lc;
	uint32_t	i;

	i = 0;
	lc = map->macho_lc;
	while (i < map->macho_header.ncmds)
	{
		if (map->file_size <
			(size_t)(((char *)lc - (char *)map->file_addr) + lc->cmdsize))
		{
			ft_fdprint(2, "File %s is corrupted : Load commands errors.\n",
				map->file_name);
			return (map_release(map));
		}
		if ((lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
			&& NULL == map_check_segments(map, lc))
			return (NULL);
		if (lc->cmd == LC_SYMTAB
			&& NULL == map_check_symtab(map, lc))
			return (NULL);
		lc = (t_lc *)((char *)lc + lc->cmdsize);
		i++;
	}
	return (map);
}

t_mapfile		*map_macho_file(t_mapfile *map)
{
	if (map_macho_getheader(map) == NULL)
		return (NULL);
	if (map_macho_getlc(map) == NULL)
		return (NULL);
	if (map_macho_checklc(map) == NULL)
		return (NULL);
	return (map);
}
