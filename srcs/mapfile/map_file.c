#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <ar.h>

#include "mapfile.h"
#include "libft.h"

static t_type		map_detect_type(t_mapfile *map)
{
	if (map->file_size < sizeof(uint32_t))
	{
		ft_fdprint(2, "File : %s is of an unknown type\n", map->file_name);
		return (UNKNOW);
	}
	map->magic = *(uint32_t *)map->file_addr;
	if (misc_is_macho_file(map->magic))
		return (MACHO);
	else if (misc_is_fat(map->magic))
		return (FAT);
	if (map->file_size >= SARMAG
		&& !ft_strncmp(map->file_addr, ARMAG, SARMAG))
	{
		return (ARCH);
	}
	ft_fdprint(2, "File : %s is of an unknown type\n", map->file_name);	
	return (UNKNOW);
}

static t_mapfile	*get_map_struct(t_mapfile *map_arg)
{
	t_mapfile		*map;

	if (NULL == (map = map_arg))
	{
		map = (t_mapfile *)ft_memalloc(sizeof(t_mapfile));
	}
	return (map);
}

t_mapfile			*map_release(t_mapfile *map)
{
	static int		malloced;

	if (map == NULL)
	{
		malloced = 1;
	}
	else if (malloced)
	{
		free(map);
	}
	return (NULL);
}

t_mapfile			*map_appropriate(t_mapfile *map)
{
	if (map->file_type == MACHO)
		return(map_macho_file(map));
	if (map->file_type == FAT)
		return (map_fat_file(map));
	return (map_arch_file(map));
}

t_mapfile			*map_file_from_mem(
	t_mapfile *map_arg, char *file_name, void *file_addr, size_t file_size)
{
	t_mapfile		*map;

	if (NULL == (map = get_map_struct(map_arg)))
		return (map_release(map));
	map->file_name = file_name;
	map->file_size = file_size;
	map->file_addr = file_addr;
	if (UNKNOW == (map->file_type = map_detect_type(map)))
		return (map_release(map));
	return (map_appropriate_file(map));
}