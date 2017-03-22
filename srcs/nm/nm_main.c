/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:31:22 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:31:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "mapfile.h"
#include "libft.h"
#include "option.h"

static void			ft_usage(void)
{
	ft_fdprint(2, "%s\n", ERR_USAGE);
}

static void			ft_help(void)
{
	ft_usage();
	ft_fdprint(2, "    -h    Display this help text.\n");
	ft_fdprint(2, "    -a    Display all even those included by debugger.\n");
	ft_fdprint(2, "    -g    Display only global (external) symbols.\n");
	ft_fdprint(2, "    -n    Sort numerically rather than alphabetically.\n");
	ft_fdprint(2, "    -p    Don't sort; display in symbol-table order.\n");
	ft_fdprint(2, "    -r    Sort in reverse order.\n");
	ft_fdprint(2, "    -u    Display only undefined symbols.\n");
	ft_fdprint(2, "    -U    Don't display undefined symbols.\n");
	ft_fdprint(2, "    -j    Just display the symbol names (no value or type)."
		"\n");
	ft_fdprint(2, "    -x    The value shall be written in hexadecimal.\n");
}

static int			get_option(int *option, int ac, char **av)
{
	int				c;
	char			*optstring;

	optstring = NM_OPTIONS;
	while ((c = option_getopt(&(t_arguments){ac, av, 0}, optstring)) != -1)
	{
		if ((char)c == '?')
		{
			ft_fdprint(2, "Unknown option `-%c'.\n", g_option_optopt);
			ft_usage();
			return (-1);
		}
		else if ((char)c == 'h')
		{
			ft_help();
			return (-1);
		}
		else
		{
			*option |= 1 << (ft_strchr(optstring, (char)c) - optstring);
		}
	}
	return (0);
}

static void			nm(t_ofile *ofile, int options, int show)
{
	t_symtab		*stlist;

	if ((stlist = nm_get_stlist(ofile, show, options)))
	{
		stlist = nm_stlist_sort(stlist, options);
		nm_stlist_display(stlist, ofile, options);
		nm_stlist_free(stlist);
	}
}

int					main(int ac, char **av)
{
	int				i;
	int				status;
	int				options;
	t_ofile			*ofile;

	i = 0;
	options = 0;
	status = EXIT_SUCCESS;
	if ((get_option(&options, ac, av)) == -1)
		return (EXIT_FAILURE);
	av += g_option_optind;
	ac -= g_option_optind;
	while (i < ac || (i == 0 && !av[i]))
	{
		if ((ofile = mapfile((i == 0 && !av[i]) ? "a.out" : av[i])) == 0)
		{
			status = EXIT_FAILURE;
			break ;
		}
		nm(ofile, options, ac > 1);
		unmapfile(ofile);
		++i;
	}
	return (status);
}
