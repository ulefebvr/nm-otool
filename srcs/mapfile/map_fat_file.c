#include "mapfile.h"

t_mapfile		*map_check_arch_64(t_mapfile *map)
{
	void	*save_file_addr;
	uint32_t save_file_size;
	uint32_t nfat_arch;

	nfat_arch = map->fat_header->nfat_arch;
	while (nfat_arch)
	{
		if (map->fat_ah_64[nfat_arch].cputype == CPU_TYPE_X86_64)
		{
			save_file_addr = map->file_addr;
			map->file_addr = map->file_addr + map->fat_ah_64[nfat_arch].offset;
			save_file_size = map->file_size;
			map->file_size = map->fat_ah_64[nfat_arch].size;
			if (map_file_from_mem(map, NULL, NULL, NULL) == NULL)
				return (NULL);
			map->file_addr = save_file_addr;
			map->file_size = save_file_size;
			return (map);
		}
		nfat_arch--;
	}
	return (map);
}

t_mapfile		*map_check_arch_32(t_mapfile *map)
{
	void	*save_file_addr;
	uint32_t save_file_size;
	uint32_t nfat_arch;

	nfat_arch = map->fat_header->nfat_arch;
	while (nfat_arch)
	{
		if (map->fat_ah_32[nfat_arch].cputype == CPU_TYPE_X86_64)
		{
			save_file_addr = map->file_addr;
			map->file_addr = map->file_addr + map->fat_ah_32[nfat_arch].offset;
			save_file_size = map->file_size;
			map->file_size = map->fat_ah_32[nfat_arch].size;
			if (map_file_from_mem(map, NULL, NULL, NULL) == NULL)
				return (NULL);
			map->file_addr = save_file_addr;
			map->file_size = save_file_size;
			return (map);
		}
		nfat_arch--;
	}
	return (map);
}

t_mapfile		*map_check_arch(t_mapfile *map)
{
	if (map->fat_subtype == 32)
		return (map_check_arch_32(map));
	else
		return (map_check_arch_64(map));
}

t_subtype		get_fat_subtype(t_mapfile *map)
{
	if (map->magic == FAT_MAGIC || map->magic == FAT_CIGAM)
	{
		map->fat_swap = (map->magic == FAT_CIGAM);
		map->magic = swap_uint32_t(map->magic, &map->fat_swap);
		return (B32);
	}
	else if (map->magic == FAT_MAGIC_64 || map->magic == FAT_CIGAM_64)
	{
		map->fat_swap = (map->magic == FAT_CIGAM_64);
		map->magic = swap_uint32_t(map->magic, &map->fat_swap);
		return (B64);
	}
	return (0);
}

t_mapfile		*map_get_arch_header(t_mapfile *map)
{
	if (map->fat_subtype == 32)
	{
		if (map->file_size < sizeof(t_fh) + sizeof(t_fa32))
		{
			ft_fdprint(2, "File %s is corrupted (no arch header)\n", map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->fat_ah_32, map->file_addr + sizeof(t_fh), sizeof(t_fa32));
		map->fat_ah_32.cputype = swap_uint32_t(map->fat_ah_32.cputype, map->fat_swap);
		map->fat_ah_32.cpusubtype = swap_uint32_t(map->fat_ah_32.cpusubtype, map->fat_swap);
		map->fat_ah_32.offset = swap_uint32_t(map->fat_ah_32.offset, map->fat_swap);
		map->fat_ah_32.size = swap_uint32_t(map->fat_ah_32.size, map->fat_swap);
		map->fat_ah_32.align = swap_uint32_t(map->fat_ah_32.align, map->fat_swap);
	}
	else
	{
		if (map->file_size < sizeof(t_fh) + sizeof(t_fa64))
		{
			ft_fdprint(2, "File %s is corrupted (no arch header)\n", map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->fat_ah_64, map->file_addr + sizeof(t_fh), sizeof(t_fa64));
		map->fat_ah_64.cputype = swap_uint32_t(map->fat_ah_64.cputype, map->fat_swap);
		map->fat_ah_64.cpusubtype = swap_uint32_t(map->fat_ah_64.cpusubtype, map->fat_swap);
		map->fat_ah_64.offset = swap_uint64_t(map->fat_ah_64.offset, map->fat_swap);
		map->fat_ah_64.size = swap_uint64_t(map->fat_ah_64.size, map->fat_swap);
		map->fat_ah_64.align = swap_uint32_t(map->fat_ah_64.align, map->fat_swap);
	}
	return (map);
}

t_mapfile		*map_get_header(t_mapfile *map)
{
	map->fat_subtype = get_fat_subtype(map);
	if (map->fat_subtype == 32 || map->fat_subtype == 64)
	{
		if (map->file_size < sizeof(t_fh))
		{
			ft_fdprint(2, "File %s is corrupted (no fat header)\n", map->file_name);
			return (map_release(map));
		}
		ft_memcpy(&map->fat_header, map->file_addr, sizeof(t_fh));
		map->fat_header->nfat_arch = swap_uint32_t(map->fat_header, map->fat_swap);
	}
	else
	{
		ft_fdprint(2, "Internal error on file %s, not recognized\n");
		return (map_release(map));
	}
	return (map);
}

t_mapfile		*map_fat_file(t_mapfile *map)
{
	if (map_get_header(map) == NULL)
		return (NULL);
	if (map_get_arch_header(map) == NULL)
		return (NULL);
	if (map_check_arch(map) == NULL)
		return (NULL);
}