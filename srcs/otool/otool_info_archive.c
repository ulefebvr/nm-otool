/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_info_archive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:23:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:23:59 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ar.h>
#include <mach-o/ranlib.h>
#include <stdlib.h>

#include "misc.h"
#include "swap.h"
#include "otool.h"
#include "libft.h"

static int			info_ar32(t_archive *ar, t_ofile *ofile)
{
	int					i;
	t_ofile				ofile_tmp;
	struct ranlib		*ranlibs;
	t_archive			**ar_tab;

	i = -1;
	ft_bzero(&ofile_tmp, sizeof(t_ofile));
	ranlibs = (struct ranlib *)ar->ranlibs;
	ar_tab = ft_memalloc(sizeof(t_archive *) * ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
		ar_tab[i] = get_ar_header((char *)ofile->ptr, ranlibs[i].ran_off,
		sizeof(uint32_t));
	i = -1;
	sort(ar_tab, &ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
	{
		write(1, "\n", (i > 0));
		ft_print("%s(%s):\n", ofile->filename, ar_tab[i]->member_name);
		ofile_tmp.ptr = ar_tab[i]->object;
		process_otool(&ofile_tmp);
		free(ar_tab[i]);
	}
	free(ar_tab);
	return (1);
}

static int			info_ar64(t_archive *ar, t_ofile *ofile)
{
	int					i;
	t_ofile				ofile_tmp;
	struct ranlib_64	*ranlibs;
	t_archive			**ar_tab;

	i = -1;
	ft_bzero(&ofile_tmp, sizeof(t_ofile));
	ranlibs = (struct ranlib_64 *)ar->ranlibs;
	ar_tab = (t_archive **)ft_memalloc(sizeof(t_archive *) * ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
		ar_tab[i] = get_ar_header((char *)ofile->ptr, ranlibs[i].ran_off,
		sizeof(uint64_t));
	i = -1;
	sort(ar_tab, &ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
	{
		write(1, "\n", (i > 0));
		ft_print("%s(%s):\n", ofile->filename, ar_tab[i]->member_name);
		ofile_tmp.ptr = ar_tab[i]->object;
		process_otool(&ofile_tmp);
		free(ar_tab[i]);
	}
	free(ar_tab);
	return (1);
}

int					otool_info_ar(t_ofile *ofile)
{
	t_archive	*ar;
	char		*name;

	ar = NULL;
	name = get_membername(ofile);
	if (!ft_strcmp(name, SYMDEF) || !ft_strcmp(name, SYMDEF_SORTED))
	{
		ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint32_t));
		ar->nranlib = ar->size / sizeof(struct ranlib);
		info_ar32(ar, ofile);
	}
	else if (!ft_strcmp(name, SYMDEF_64) || !ft_strcmp(name, SYMDEF_64_SORTED))
	{
		ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint64_t));
		ar->nranlib = ar->size / sizeof(struct ranlib_64);
		info_ar64(ar, ofile);
	}
	free(ar);
	return (0);
}
