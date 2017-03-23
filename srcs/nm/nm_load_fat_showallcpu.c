/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_load_fat_showallcpu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:50:53 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/23 12:50:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>

#include "nm.h"
#include "misc.h"
#include "swap.h"
#include "libft.h"

static void		process_nm(t_ofile *ofile, int opt)
{
	t_symtab		*stlist;

	if ((stlist = nm_get_stlist(ofile, 0, opt | AR_T)))
	{
		stlist = nm_stlist_sort(stlist, opt | AR_T);
		nm_stlist_display(stlist, ofile, opt | AR_T);
		nm_stlist_free(stlist);
	}
}

void			show_all_cputype32(
					t_arch32 *arch, uint32_t narchs, t_ofile *ofile, int opt)
{
	uint32_t	i;
	t_ofile		s_ofile;

	i = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	ft_bzero(&s_ofile, sizeof(t_ofile));
	while (i < narchs)
	{
		ft_print("\n");
		print_cputype_nm(ofile, swap_uint32_t(arch[i].cputype, ofile->swap));
		s_ofile.ptr = ofile->ptr + swap_uint32_t(arch[i].offset, ofile->swap);
		misc_check_swap_need(*(uint32_t *)s_ofile.ptr, &s_ofile.swap);
		process_nm(&s_ofile, opt);
		i++;
	}
}

void			show_all_cputype64(
					t_arch64 *arch, uint32_t narchs, t_ofile *ofile, int opt)
{
	uint32_t	i;
	t_ofile		s_ofile;

	i = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	ft_bzero(&s_ofile, sizeof(t_ofile));
	while (i < narchs)
	{
		ft_print("\n");
		print_cputype_nm(ofile, swap_uint32_t(arch[i].cputype, ofile->swap));
		s_ofile.ptr = ofile->ptr + swap_uint64_t(arch[i].offset, ofile->swap);
		misc_check_swap_need(*(uint32_t *)s_ofile.ptr, &s_ofile.swap);
		process_nm(&s_ofile, opt);
		i++;
	}
}
