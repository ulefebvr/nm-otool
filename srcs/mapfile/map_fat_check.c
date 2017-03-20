/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fat_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:42:24 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:42:29 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"
#include "swap.h"

t_mapfile		*map_check_arch_64(t_mapfile *map)
{
	void		*save_file_addr;
	uint32_t	save_file_size;
	uint32_t	nfat_arch;
	uint32_t	i;

	nfat_arch = map->fat_header.nfat_arch;
	i = 0;
	while (i < nfat_arch)
	{
		save_file_addr = map->file_addr;
		map->file_addr = map->file_addr
			+ swap_uint64_t(map->fat_ah_64[i].offset, map->fat_swap);
		save_file_size = map->file_size;
		map->file_size = swap_uint64_t(map->fat_ah_64[i].size, map->fat_swap);
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = save_file_addr;
		map->file_size = save_file_size;
		i++;
	}
	return (map);
}

t_mapfile		*map_check_arch_32(t_mapfile *map)
{
	void		*save_file_addr;
	uint32_t	save_file_size;
	uint32_t	nfat_arch;
	uint32_t	i;

	i = 0;
	nfat_arch = map->fat_header.nfat_arch;
	while (i < nfat_arch)
	{
		save_file_addr = map->file_addr;
		map->file_addr = map->file_addr
			+ swap_uint32_t(map->fat_ah_32[i].offset, map->fat_swap);
		save_file_size = map->file_size;
		map->file_size = swap_uint32_t(map->fat_ah_32[i].size, map->fat_swap);
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = save_file_addr;
		map->file_size = save_file_size;
		i++;
	}
	return (map);
}
