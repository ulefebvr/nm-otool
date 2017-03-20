/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:15 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:15 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>

#include "libft.h"
#include "misc.h"
#include "mapfile.h"
#include "otool.h"

static void			otool(t_ofile *ofile)
{
	t_otool			otool;

	ft_bzero(&otool, sizeof(t_otool));
	if (otool_gather_information(&otool, ofile))
	{
		otool_print(&otool);
	}
}

void				process_otool(t_ofile *ofile)
{
	otool(ofile);
}

int					main(int ac, char **av)
{
	int				i;
	int				status;
	t_ofile			*ofile;

	i = 0;
	++av;
	--ac;
	status = EXIT_SUCCESS;
	while (i < ac || (i == 0 && !av[i]))
	{
		if ((ofile = mapfile((i == 0 && !av[i]) ? "a.out" : av[i])) == 0)
		{
			status = EXIT_FAILURE;
			break ;
		}
		ft_print("%s:\n", ofile->filename);
		otool(ofile);
		unmapfile(ofile);
		++i;
	}
	return (status);
}
