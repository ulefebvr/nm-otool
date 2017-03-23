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

#include "otool.h"
#include "misc.h"
#include "swap.h"
#include "libft.h"

void			show_all_cputype32(
					t_arch32 *arch, uint32_t narchs, t_ofile *ofile)
{
	uint32_t	i;
	t_ofile		s_ofile;

	i = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	ft_bzero(&s_ofile, sizeof(t_ofile));
	while (i < narchs)
	{
		print_cputype_otool(ofile, swap_uint32_t(arch[i].cputype, ofile->swap));
		s_ofile.ptr = ofile->ptr + swap_uint32_t(arch[i].offset, ofile->swap);
		misc_check_swap_need(*(uint32_t *)s_ofile.ptr, &s_ofile.swap);
		process_otool(&s_ofile, 0);
		i++;
	}
}

void			show_all_cputype64(
					t_arch64 *arch, uint32_t narchs, t_ofile *ofile)
{
	uint32_t	i;
	t_ofile		s_ofile;

	i = 0;
	narchs = swap_uint32_t(narchs, ofile->swap);
	ft_bzero(&s_ofile, sizeof(t_ofile));
	while (i < narchs)
	{
		print_cputype_otool(ofile, swap_uint32_t(arch[i].cputype, ofile->swap));
		s_ofile.ptr = ofile->ptr + swap_uint64_t(arch[i].offset, ofile->swap);
		misc_check_swap_need(*(uint32_t *)s_ofile.ptr, &s_ofile.swap);
		process_otool(&s_ofile, 0);
		i++;
	}
}
