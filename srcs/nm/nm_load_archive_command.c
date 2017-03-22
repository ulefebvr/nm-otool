/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_load_archive_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:22:04 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:22:04 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <ar.h>
#include <mach-o/ranlib.h>

#include "nm.h"
#include "swap.h"
#include "libft.h"
#include "swap.h"
#include "misc.h"

static void				process_nm(t_ofile *ofile, int opt)
{
	t_symtab		*stlist;

	if ((stlist = nm_get_stlist(ofile, 0, opt | AR_T)))
	{
		stlist = nm_stlist_sort(stlist, opt | AR_T);
		nm_stlist_display(stlist, ofile, opt | AR_T);
		nm_stlist_free(stlist);
	}
}

static void				load_archive_command32(
							t_archive *ar, t_ofile *ofile, int opt)
{
	int					i;
	struct ranlib		*ranlibs;
	t_ofile				ofile_tmp;
	t_archive			**ar_tmp;

	i = -1;
	if (ar == NULL || ar->nranlib == 0)
		return ;
	ft_bzero(&ofile_tmp, sizeof(t_ofile));
	ranlibs = (struct ranlib *)ar->ranlibs;
	ar_tmp = ft_memalloc(sizeof(t_archive *) * ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
		ar_tmp[i] = get_ar_header((char *)ofile->ptr, ranlibs[i].ran_off,
		sizeof(uint32_t));
	sort(ar_tmp, &ar->nranlib);
	i = -1;
	while ((uint32_t)(++i) < ar->nranlib)
	{
		ft_print("\n%s(%s):\n", ofile->filename, ar_tmp[i]->member_name);
		ofile_tmp.ptr = ar_tmp[i]->object;
		process_nm(&ofile_tmp, opt);
		free(ar_tmp[i]);
	}
	free(ar_tmp);
}

static void				load_archive_command64(
							t_archive *ar, t_ofile *ofile, int opt)
{
	int					i;
	struct ranlib_64	*ranlibs;
	t_ofile				ofile_tmp;
	t_archive			**ar_tmp;

	i = -1;
	if (ar == NULL || ar->nranlib == 0)
		return ;
	ft_bzero(&ofile_tmp, sizeof(t_ofile));
	ranlibs = (struct ranlib_64 *)ar->ranlibs;
	ar_tmp = ft_memalloc(sizeof(t_archive *) * ar->nranlib);
	while ((uint32_t)(++i) < ar->nranlib)
		ar_tmp[i] = get_ar_header((char *)ofile->ptr, ranlibs[i].ran_off,
		sizeof(uint64_t));
	sort(ar_tmp, &ar->nranlib);
	i = -1;
	while ((uint32_t)(++i) < ar->nranlib)
	{
		ft_print("\n%s(%s):\n", ofile->filename, ar_tmp[i]->member_name);
		ofile_tmp.ptr = ar_tmp[i]->object;
		process_nm(&ofile_tmp, opt);
		free(ar_tmp[i]);
	}
	free(ar_tmp);
}

t_symtab				*nm_load_archive_command(t_ofile *ofile, int options)
{
	t_archive			*ar;
	char				*name;

	ar = NULL;
	name = get_membername(ofile);
	if (!ft_strcmp(name, SYMDEF) || !ft_strcmp(name, SYMDEF_SORTED))
	{
		ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint32_t));
		ar->nranlib = ar->size / sizeof(struct ranlib);
		load_archive_command32(ar, ofile, options);
	}
	else if (!ft_strcmp(name, SYMDEF_64) || !ft_strcmp(name, SYMDEF_64_SORTED))
	{
		ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint64_t));
		ar->nranlib = ar->size / sizeof(struct ranlib_64);
		load_archive_command64(ar, ofile, options);
	}
	free(ar);
	return (0);
}
