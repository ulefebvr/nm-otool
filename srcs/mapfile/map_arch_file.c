#include "mapfile.h"

#include "libft.h"
#include "mach-o/ranlib.h"

t_mapfile		*map_arch_check_ranlib_64(t_mapfile *map)
{
	uint32_t	i;
	char 		*function_name;
	void 		*tmp;

	i = 0;
	tmp = map->file_addr;
	while (i < map->arch_nranlib)
	{
		function_name = (char *)map->file_addr + map->arch_rl64[i].ran_off + sizeof(t_ar);
		map->file_addr = (tmp + map->arch_rl64[i].ran_off + sizeof(t_ar) + ft_atoi(((t_ar *)((char *)map->file_addr + map->arch_rl64[i].ran_off))->ar_name + 3));
		map->file_name = function_name;
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = tmp;
		i++;
	}
	return (map);
}

t_mapfile		*map_arch_check_ranlib_32(t_mapfile *map)
{
	uint32_t	i;
	char 		*function_name;
	void 		*tmp;

	i = 0;
	tmp = map->file_addr;
	while (i < map->arch_nranlib)
	{
		function_name = (char *)map->file_addr + map->arch_rl32[i].ran_off + sizeof(t_ar);
		map->file_addr = (tmp + map->arch_rl32[i].ran_off + sizeof(t_ar) + ft_atoi(((t_ar *)((char *)map->file_addr + map->arch_rl32[i].ran_off))->ar_name + 3));
		map->file_name = function_name;
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = tmp;
		i++;
	}
	return (map);
}

t_mapfile		*map_arch_get_ranlib(t_mapfile *map)
{
	size_t		file_size;

	file_size = ft_atoi(((t_ar *)(map->file_addr + SARMAG))->ar_size);
	if (map->file_size < (SARMAG + sizeof(t_ar) + 20 + sizeof(uint32_t) + file_size))
	{
		ft_fdprint(2, "File %s is corrupted\n", map->file_name);
		return (map_release(map));
	}
	if (map->arch_subtype == B32)
		map->arch_rl32 = (t_rl32 *)(map->file_addr + SARMAG + sizeof(t_ar) + 20 + sizeof(uint32_t));
	else
		map->arch_rl64 = (t_rl64 *)(map->file_addr + SARMAG + sizeof(t_ar) + 20 + sizeof(uint32_t));
	return (map);
}

t_mapfile		*map_arch_get_nranlib(t_mapfile *map)
{
	uint32_t	size;

	if (map->file_size < (SARMAG + sizeof(t_ar) + 20 + sizeof(uint32_t)))
	{
		ft_fdprint(2, "File %s is corrupted\n", map->file_name);
		return (map_release(map));
	}
	size = *(uint32_t *)(map->file_addr + SARMAG + sizeof(t_ar) + 20);
	if (map->arch_subtype == B32)
		map->arch_nranlib = size / sizeof(t_rl32);
	else
		map->arch_nranlib = size / sizeof(t_rl64);
	return (map);	
}

t_mapfile		*map_arch_get_header(t_mapfile *map)
{
	if (map->file_size < (sizeof(t_ar) + SARMAG))
	{
		ft_fdprint(2, "File %s is corrupted (no ar header)\n", map->file_name);
		return (map_release(map));
	}
	ft_memcpy(&map->arch_header, (map->file_addr + SARMAG), sizeof(t_ar));
	return (map);
}

t_subtype		map_arch_get_subtype(t_mapfile *map)
{
	char *symdef;

	symdef = (char *)(map->file_addr + SARMAG + sizeof(t_ar));
	if (!strcmp(symdef, SYMDEF) || !strcmp(symdef, SYMDEF_SORTED))
		return (B32);
	return (B64);
}

t_mapfile		*map_arch_file(t_mapfile *map)
{
	map->arch_subtype = map_arch_get_subtype(map);
	if (map_arch_get_header(map) == NULL)
		return (NULL);
	if (map_arch_get_nranlib(map) == NULL)
		return (NULL);
	if (map_arch_get_ranlib(map) == NULL)
		return (NULL);
	if (map->arch_subtype == B32 && map_arch_check_ranlib_32(map) == NULL)
		return (NULL);
	else if (map->arch_subtype == B64 && map_arch_check_ranlib_64(map) == NULL)
		return (NULL);
	return (map);
}