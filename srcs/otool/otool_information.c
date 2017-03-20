/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:11 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:12 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <ar.h>

#include "libft.h"
#include "misc.h"
#include "otool.h"
#include "swap.h"

int				otool_gather_information(t_otool *otool, t_ofile *ofile)
{
	int				ret;
	uint32_t		magic;

	ret = 0;
	magic = *(uint32_t *)ofile->ptr;
	misc_check_swap_need(magic, &ofile->swap);
	misc_check_filetype(swap_uint32_t(magic, ofile->swap), &ofile->filetype);
	if (misc_is_macho_file(magic))
	{
		ret = otool_info_macho(swap_uint32_t(magic, ofile->swap), otool, ofile);
	}
	else if (misc_is_fat(magic))
	{
		ret = otool_info_fat(swap_uint32_t(magic, ofile->swap), otool, ofile);
	}
	else if (!ft_strncmp(ofile->ptr, ARMAG, SARMAG))
	{
		ret = otool_info_ar(ofile);
	}
	else if (ft_fdprint(2, "%s\n", "Unrecognized file format"))
		return (0);
	return (ret);
}
