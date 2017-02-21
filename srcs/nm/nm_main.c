#include "nm.h"
#include "mapfile.h"
#include "libft.h"
#include "option.h"

static void			ft_usage(void)
{
	ft_fdprint(2, "%s\n", ERR_USAGE);
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
			ft_usage();
			return (-1);
		}
		else
		{
			*option |= 1 << (ft_strchr(optstring, (char)c) - optstring);
		}
	}
	return (0);
}

static void			nm(t_ofile *ofile, int options)
{
	t_symtab		*stlist;

	stlist = nm_get_stlist(ofile);
	stlist = nm_stlist_sort(stlist, options);
	nm_stlist_display(stlist, ofile, options);
	nm_stlist_free(stlist);
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
		nm(ofile, options);
		unmapfile(ofile);
		++i;
	}
	return (status);
}
