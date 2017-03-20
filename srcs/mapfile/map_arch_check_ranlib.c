/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arch_check_ranlib.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:27:13 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:27:13 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"
#include "libft.h"

#include "mach-o/ranlib.h"

t_mapfile		*map_arch_check_ranlib_64(t_mapfile *map)
{
	uint32_t	i;
	char		*function_name;
	void		*tmp;

	i = 0;
	tmp = map->file_addr;
	while (i < map->arch_nranlib)
	{
		function_name = (char *)map->file_addr + map->arch_rl64[i].ran_off
			+ sizeof(t_ar);
		map->file_addr = (tmp + map->arch_rl64[i].ran_off + sizeof(t_ar)
			+ ft_atoi(((t_ar *)((char *)map->file_addr
			+ map->arch_rl64[i].ran_off))->ar_name + 3));
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
	char		*function_name;
	void		*tmp;

	i = 0;
	tmp = map->file_addr;
	while (i < map->arch_nranlib)
	{
		function_name = (char *)map->file_addr + map->arch_rl32[i].ran_off
			+ sizeof(t_ar);
		map->file_addr = (tmp + map->arch_rl32[i].ran_off + sizeof(t_ar)
			+ ft_atoi(((t_ar *)((char *)map->file_addr
			+ map->arch_rl32[i].ran_off))->ar_name + 3));
		map->file_name = function_name;
		if (map_file_from_mem(map, NULL, NULL, 0) == NULL)
			return (NULL);
		map->file_addr = tmp;
		i++;
	}
	return (map);
}
