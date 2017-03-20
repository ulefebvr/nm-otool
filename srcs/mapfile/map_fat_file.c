/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fat_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:20:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:20:38 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"

#include "swap.h"
#include "libft.h"

#include <stdio.h>

t_mapfile		*map_check_arch(t_mapfile *map)
{
	t_mapfile	*ret;

	if (map->fat_subtype == B32)
		ret = map_check_arch_32(map);
	else
		ret = map_check_arch_64(map);
	if (!ret)
		ft_fdprint(2, "File %s is corrupted (no arch header)\n",
			map->file_name);
	return (ret);
}

t_subtype		get_fat_subtype(t_mapfile *map)
{
	if (map->magic == FAT_MAGIC || map->magic == FAT_CIGAM)
	{
		map->fat_swap = (map->magic == FAT_CIGAM);
		map->magic = swap_uint32_t(map->magic, map->fat_swap);
		return (B32);
	}
	else if (map->magic == FAT_MAGIC_64 || map->magic == FAT_CIGAM_64)
	{
		map->fat_swap = (map->magic == FAT_CIGAM_64);
		map->magic = swap_uint32_t(map->magic, map->fat_swap);
		return (B64);
	}
	return (0);
}

t_mapfile		*map_get_arch_header(t_mapfile *map)
{
	if (map->fat_subtype == B32)
	{
		if (map->file_size < (sizeof(t_fh) + sizeof(uint32_t) + sizeof(t_fa32)))
		{
			ft_fdprint(2, "File %s is corrupted (no arch header)\n",
				map->file_name);
			return (map_release(map));
		}
		map->fat_ah_32 = (t_fa32 *)((char *)map->file_addr + sizeof(t_fh));
	}
	else
	{
		if (map->file_size < (sizeof(t_fh) + sizeof(uint32_t) + sizeof(t_fa64)))
		{
			ft_fdprint(2, "File %s is corrupted (no arch header)\n",
				map->file_name);
			return (map_release(map));
		}
		map->fat_ah_64 = (t_fa64 *)((char *)map->file_addr + sizeof(t_fh));
	}
	return (map);
}

t_mapfile		*map_get_fat_header(t_mapfile *map)
{
	map->fat_subtype = get_fat_subtype(map);
	if (map->fat_subtype == B32 || map->fat_subtype == B64)
	{
		if (map->file_size < sizeof(t_fh) + sizeof(uint32_t))
		{
			ft_fdprint(2, "File %s is corrupted (no fat header)\n",
				map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->fat_header, map->file_addr, sizeof(t_fh));
		map->fat_header.nfat_arch =
			swap_uint32_t(map->fat_header.nfat_arch, map->fat_swap);
		map->fat_header.magic =
			swap_uint32_t(map->fat_header.magic, map->fat_swap);
	}
	else
	{
		ft_fdprint(2, "Internal error on file %s, not recognized\n",
			map->file_name);
		return (map_release(map));
	}
	return (map);
}

t_mapfile		*map_fat_file(t_mapfile *map)
{
	if (map_get_fat_header(map) == NULL)
		return (NULL);
	if (map_get_arch_header(map) == NULL)
		return (NULL);
	if (map_check_arch(map) == NULL)
		return (NULL);
	return (map);
}
