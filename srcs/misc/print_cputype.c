/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cputype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:46:11 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/23 16:46:12 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>

#include "misc.h"
#include "libft.h"

void		print_cputype(t_ofile *ofile, cpu_type_t cputype, char *s)
{
	if (cputype == CPU_TYPE_VAX)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "vax");
	else if (cputype == CPU_TYPE_MC680x0)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "mc680");
	else if (cputype == CPU_TYPE_X86 || cputype == CPU_TYPE_I386)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "i386");
	else if (cputype == CPU_TYPE_X86_64)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "x86_64");
	else if (cputype == CPU_TYPE_MC98000)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "mc98000");
	else if (cputype == CPU_TYPE_HPPA)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "hppa");
	else if (cputype == CPU_TYPE_ARM)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "arm");
	else if (cputype == CPU_TYPE_MC88000)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "mc880000");
	else if (cputype == CPU_TYPE_SPARC)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "sparc");
	else if (cputype == CPU_TYPE_I860)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "i860");
	else if (cputype == CPU_TYPE_POWERPC)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "ppc");
	else if (cputype == CPU_TYPE_POWERPC64)
		ft_print("%s (%sarchitecture %s):\n", ofile->filename, s, "ppc64");
}

void		print_cputype_nm(t_ofile *ofile, cpu_type_t cputype)
{
	print_cputype(ofile, cputype, "for ");
}

void		print_cputype_otool(t_ofile *ofile, cpu_type_t cputype)
{
	print_cputype(ofile, cputype, "");
}
