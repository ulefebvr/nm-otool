#include "mapfile.h"

#include "swap.h"
#include "libft.h"

#include <stdio.h>
t_mapfile		*map_check_arch_64(t_mapfile *map)
{
	void	*save_file_addr;
	uint32_t save_file_size;
	uint32_t nfat_arch;
	uint32_t i;

	nfat_arch = map->fat_header.nfat_arch;
	i = 0;
	while (i < nfat_arch)
	{
		save_file_addr = map->file_addr;
		map->file_addr = map->file_addr + swap_uint64_t(map->fat_ah_64[i].offset, map->fat_swap);
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
	void	*save_file_addr;
	uint32_t save_file_size;
	uint32_t nfat_arch;

	nfat_arch = map->fat_header.nfat_arch;
	while (nfat_arch--)
	{
		save_file_addr = map->file_addr;
		map->file_addr = map->file_addr + swap_uint32_t(map->fat_ah_32[nfat_arch].offset, map->fat_swap);
		save_file_size = map->file_size;
		map->file_size = swap_uint32_t(map->fat_ah_32[nfat_arch].size, map->fat_swap);
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = save_file_addr;
		map->file_size = save_file_size;
	}
	return (map);
}

t_mapfile		*map_check_arch(t_mapfile *map)
{
	t_mapfile	*ret;

	if (map->fat_subtype == B32)
		ret = map_check_arch_32(map);
	else
		ret = map_check_arch_64(map);
	if (!ret)
		ft_fdprint(2, "File %s is corrupted (no arch header)\n", map->file_name);
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
			ft_fdprint(2, "File %s is corrupted (no arch header)\n", map->file_name);
			return (map_release(map));
		}
		map->fat_ah_32 = (t_fa32 *)((char *)map->file_addr + sizeof(t_fh));
	}
	else
	{
		if (map->file_size < (sizeof(t_fh) + sizeof(uint32_t) + sizeof(t_fa64)))
		{
			ft_fdprint(2, "File %s is corrupted (no arch header)\n", map->file_name);
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
			ft_fdprint(2, "File %s is corrupted (no fat header)\n", map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->fat_header, map->file_addr, sizeof(t_fh));
		map->fat_header.nfat_arch = swap_uint32_t(map->fat_header.nfat_arch, map->fat_swap);
		map->fat_header.magic = swap_uint32_t(map->fat_header.magic, map->fat_swap);
	}
	else
	{
		ft_fdprint(2, "Internal error on file %s, not recognized\n", map->file_name);
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
