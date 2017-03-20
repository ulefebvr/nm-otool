/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_macho_nlists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:28:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 11:28:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapfile.h"
#include "swap.h"

#include "libft.h"

t_mapfile		*map_check_nlist32(t_mapfile *map)
{
	uint32_t			i;
	struct nlist		*symbole_tab;

	i = 0;
	if (map->file_size < map->macho_symtab.symoff
		+ sizeof(struct nlist) * map->macho_symtab.nsyms)
	{
		ft_fdprint(2, "File %s, Error on nlist\n", map->file_name);
		return (map_release(map));
	}
	symbole_tab = (struct nlist *)((char *)map->file_addr
		+ map->macho_symtab.symoff);
	while (i < map->macho_symtab.nsyms)
	{
		if (swap_uint32_t(symbole_tab[i].n_un.n_strx, map->macho_swap)
			> map->macho_symtab.strsize)
			return (map_release(map));
		i++;
	}
	return (map);
}

t_mapfile		*map_check_nlist64(t_mapfile *map)
{
	uint32_t			i;
	struct nlist_64		*symbole_tab;

	i = 0;
	if (map->file_size < map->macho_symtab.symoff
		+ sizeof(struct nlist) * map->macho_symtab.nsyms)
	{
		ft_fdprint(2, "File %s, Error on nlist\n", map->file_name);
		return (map_release(map));
	}
	symbole_tab = (struct nlist_64 *)((char *)map->file_addr
		+ map->macho_symtab.symoff);
	while (i < map->macho_symtab.nsyms)
	{
		if (swap_uint32_t(symbole_tab[i].n_un.n_strx, map->macho_swap)
			> map->macho_symtab.strsize)
			return (map_release(map));
		i++;
	}
	return (map);
}

t_mapfile		*map_check_symtab(t_mapfile *map, t_lc *lc_symtab)
{
	if (map->file_size <
		(size_t)((char *)lc_symtab - (char *)map->file_addr + sizeof(t_sytab)))
		return (map_release(map));
	if (lc_symtab->cmd == LC_SYMTAB)
	{
		ft_memcpy(&map->macho_symtab, lc_symtab, sizeof(t_sytab));
		map->macho_symtab.cmdsize =
			swap_uint32_t(map->macho_symtab.cmdsize, map->macho_swap);
		map->macho_symtab.symoff =
			swap_uint32_t(map->macho_symtab.symoff, map->macho_swap);
		map->macho_symtab.nsyms =
			swap_uint32_t(map->macho_symtab.nsyms, map->macho_swap);
		map->macho_symtab.stroff =
			swap_uint32_t(map->macho_symtab.stroff, map->macho_swap);
		map->macho_symtab.strsize =
			swap_uint32_t(map->macho_symtab.strsize, map->macho_swap);
		return ((map->macho_header.magic == MH_MAGIC) ?
			map_check_nlist32(map) : map_check_nlist64(map));
	}
	return (map_release(map));
}
