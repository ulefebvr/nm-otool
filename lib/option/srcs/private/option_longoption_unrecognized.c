/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_longoption_unrecognized.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:12 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:12 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

/*
** Can't find it as a long option.  If this is not getopt_long_only,
** or the option starts with '--' or is not a valid short
** option, then it's an error.
** Otherwise interpret it as a short option.
*/

int		option_treat_longoption_unrecognized(char **argv, t_option_data *d)
{
	if (d->opterr)
	{
		if (argv[d->optind][1] == '-')
			option_ft_fdprint(2, "%s: unrecognized option '--%s'\n",
				argv[0], d->private_nextchar);
		else
			option_ft_fdprint(2, "%s: unrecognized option '%c%s'\n",
				argv[0], argv[d->optind][0], d->private_nextchar);
	}
	d->private_nextchar = (char *)"";
	d->optind++;
	d->optopt = 0;
	return ('?');
}
