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

	size_struct = sizeof(t_mh) + ((map->macho_subtype == B64) * sizeof(uint32_t));
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

void			add_section32(
	t_mapfile *map, t_s64 *macho_sections, t_s32 *section, uint32_t i)
{
	ft_memcpy(macho_sections[i].sectname, section[i].sectname, 16);
	ft_memcpy(macho_sections[i].segname, section[i].segname, 16);
	macho_sections[i].addr = 
		(uint64_t)swap_uint32_t(section[i].addr, map->macho_swap);
	macho_sections[i].size = 
		(uint64_t)swap_uint32_t(section[i].size, map->macho_swap);
	macho_sections[i].offset = 
		swap_uint32_t(section[i].offset, map->macho_swap);
	macho_sections[i].align = 
		swap_uint32_t(section[i].align, map->macho_swap);
	macho_sections[i].reloff = 
		swap_uint32_t(section[i].reloff, map->macho_swap);
	macho_sections[i].nreloc = 
		swap_uint32_t(section[i].nreloc, map->macho_swap);
	macho_sections[i].flags = 
		swap_uint32_t(section[i].flags, map->macho_swap);
}

void			add_section64(
	t_mapfile *map, t_s64 *macho_sections, t_s64 *section, uint32_t i)
{
	ft_memcpy(macho_sections[i].sectname, section[i].sectname, 16);
	ft_memcpy(macho_sections[i].segname, section[i].segname, 16);
	macho_sections[i].addr = 
		swap_uint64_t(section[i].addr, map->macho_swap);
	macho_sections[i].size = 
		swap_uint64_t(section[i].size, map->macho_swap);
	macho_sections[i].offset = 
		swap_uint32_t(section[i].offset, map->macho_swap);
	macho_sections[i].align = 
		swap_uint32_t(section[i].align, map->macho_swap);
	macho_sections[i].reloff = 
		swap_uint32_t(section[i].reloff, map->macho_swap);
	macho_sections[i].nreloc = 
		swap_uint32_t(section[i].nreloc, map->macho_swap);
	macho_sections[i].flags = 
		swap_uint32_t(section[i].flags, map->macho_swap);
}

t_mapfile		*map_add_section(
	t_mapfile *map, void *section, uint32_t i, uint32_t nsects)
{
	if (i == 0 && !map->macho_sections)
	{
		if (!(map->macho_sections = ft_memalloc(sizeof(t_s64) * nsects)))
			return (map_release(map));
	}
	if (map->macho_subtype == B32)
	{
		add_section32(map, map->macho_sections, (t_s32 *)section, i);		
	}
	else
	{
		add_section64(map, map->macho_sections, (t_s64 *)section, i);
	}
	return (map);
}

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
	ft_fdprint(2, "\033[32m%d\033[0m\n", (map->macho_swap == 1));
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
			ft_fdprint(2, "File %s is corrupted : Load commands errors.",
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
