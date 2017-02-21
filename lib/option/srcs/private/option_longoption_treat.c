/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_longoption_treat.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:14 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:15 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

int		option_treat_longoption(int argc, char **argv, t_option_data *d)
{
	t_treat_longoption info;

	info = (t_treat_longoption){0, 0, 0, 0, 0, 0, 0, 0};
	info.namelen = option_treat_longoption_get_namelen(&info, d);
	option_treat_longoption_test_match(&info, d);
	if (info.ambig_list != 0 && !info.exact)
		return (option_treat_longoption_ambiguous(argv, &info, d));
	if (info.pfound != 0)
	{
		return (option_treat_longoption_arguments(
			&(t_arguments){argc, argv, 0}, &info, d));
	}
	if (!d->long_only || argv[d->optind][1] == '-'
		|| option_ft_strchr(d->optstring, *d->private_nextchar) == 0)
		return (option_treat_longoption_unrecognized(argv, d));
	return (0);
}
