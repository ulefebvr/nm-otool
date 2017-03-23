/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_host_cputype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:17:39 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/23 12:17:39 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>

#include "otool.h"
#include "swap.h"
#include "misc.h"

#include "libft.h"

int			no_host_cputype32(t_arch32 *arch, uint32_t narchs, t_ofile *ofile)
{
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == HOST_CPU)
		{
			return (0);
		}
	}
	return (1);
}

int			no_host_cputype64(t_arch64 *arch, uint32_t narchs, t_ofile *ofile)
{
	narchs = swap_uint32_t(narchs, ofile->swap);
	while (narchs--)
	{
		if (swap_uint32_t(arch[narchs].cputype, ofile->swap) == HOST_CPU)
		{
			return (0);
		}
	}
	return (1);
}
