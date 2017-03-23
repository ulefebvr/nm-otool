/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_stlist_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:31:49 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:31:49 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>

#include "nm.h"
#include "swap.h"
#include "libft.h"

static char			*section_64(t_ofile *ofile, uint8_t n_sect, char swap)
{
	uint32_t			i;
	uint32_t			ncmds;
	t_lc				*tmp_lc;
	struct section_64	*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = ofile->lc;
	n_sect -= 1;
	while (ncmds < ofile->ncmds)
	{
		if (swap_uint32_t(tmp_lc->cmd, swap) == LC_SEGMENT_64)
		{
			tmp_sect = (struct section_64 *)((char *)tmp_lc + sizeof(t_sc64));
			if (n_sect < i + swap_uint32_t(((t_sc64 *)tmp_lc)->nsects, swap))
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += swap_uint32_t(((t_sc64 *)tmp_lc)->nsects, swap);
		}
		tmp_lc = (t_lc *)((char *)tmp_lc
			+ swap_uint32_t(tmp_lc->cmdsize, swap));
		++ncmds;
	}
	return (0);
}

static char			*section_32(t_ofile *ofile, uint8_t n_sect, char swap)
{
	uint32_t			i;
	uint32_t			ncmds;
	t_lc				*tmp_lc;
	struct section		*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = ofile->lc;
	n_sect -= 1;
	while (ncmds < ofile->ncmds)
	{
		if (swap_uint32_t(tmp_lc->cmd, swap) == LC_SEGMENT)
		{
			tmp_sect = (struct section *)((char *)tmp_lc + sizeof(t_sc32));
			if (n_sect < i + swap_uint32_t(((t_sc32 *)tmp_lc)->nsects, swap))
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += swap_uint32_t(((t_sc32 *)tmp_lc)->nsects, swap);
		}
		tmp_lc = (t_lc *)((char *)tmp_lc
			+ swap_uint32_t(tmp_lc->cmdsize, swap));
		++ncmds;
	}
	return (0);
}

static char			get_type_letter(
	t_ofile *ofile, uint8_t n_type, uint64_t n_value, uint8_t n_sect)
{
	char			type;
	char			*section_name;

	type = 0;
	type = ((n_type & N_TYPE) == N_INDR) ? 'I' : type;
	type = (!type && (n_type & N_TYPE) == N_STAB) ? '-' : type;
	type = (!type && (n_type & N_TYPE) == N_UNDF
		&& (n_type & N_EXT) && n_value != 0) ? 'C' : type;
	type = (!type && (n_type & N_TYPE) == N_UNDF
		&& (n_type & N_TYPE) == N_PBUD) ? 'u' : type;
	type = (!type && (n_type & N_TYPE) == N_UNDF) ? 'U' : type;
	type = (!type && (n_type & N_TYPE) == N_ABS) ? 'A' : type;
	if (!type && (n_type & N_TYPE) == N_SECT)
	{
		section_name = (ofile->filetype == 8) ?
			section_32(ofile, n_sect, ofile->swap)
			: section_64(ofile, n_sect, ofile->swap);
		if (section_name && (!ft_strcmp(section_name, SECT_TEXT)
			|| !ft_strcmp(section_name, SECT_DATA)
			|| !ft_strcmp(section_name, SECT_BSS)))
			type = ft_toupper(section_name[2]);
		else
			type = 'S';
	}
	return (!(n_type & N_EXT) ? ft_tolower(type) : type);
}

t_symtab			*add_new_stlist(
	t_symtab *tail, char *stringtable, struct nlist info, t_ofile *ofile)
{
	t_symtab		*node;

	node = ft_memalloc(sizeof(t_symtab));
	if (tail)
		tail->next = node;
	node->n_strx = swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->value = swap_uint32_t(info.n_value, ofile->swap);
	node->type = get_type_letter(ofile, info.n_type,
		(uint64_t)swap_uint32_t(info.n_value, ofile->swap), info.n_sect);
	node->name = stringtable + swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->n_sect = info.n_sect;
	return (node);
}

t_symtab			*add_new_stlist_64(
	t_symtab *tail, char *stringtable, struct nlist_64 info, t_ofile *ofile)
{
	t_symtab		*node;

	node = ft_memalloc(sizeof(t_symtab));
	if (tail)
		tail->next = node;
	node->n_strx = swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->value = swap_uint64_t(info.n_value, ofile->swap);
	node->type = get_type_letter(ofile, info.n_type,
		swap_uint64_t(info.n_value, ofile->swap), info.n_sect);
	node->name = stringtable + swap_uint32_t(info.n_un.n_strx, ofile->swap);
	node->n_sect = info.n_sect;
	return (node);
}
