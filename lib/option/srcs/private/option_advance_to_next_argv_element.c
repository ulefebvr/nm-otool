/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_advance_to_next_argv_element.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:29 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"
#include "option_tools.h"

/*
** If we have just processed some options following some non-options,
** exchange them so that the options come first.
**
** Skip any additional non-options
** and extend the range of non-options previously skipped.
*/

void	option_permute_prepare(int argc, char **argv, t_option_data *d)
{
	if (d->private_first_nonopt != d->private_last_nonopt
		&& d->private_last_nonopt != d->optind)
		option_exchange((char **)argv, d);
	else if (d->private_last_nonopt != d->optind)
		d->private_first_nonopt = d->optind;
	while (d->optind < argc && NONOPTION_P)
		d->optind++;
	d->private_last_nonopt = d->optind;
}

/*
** The special ARGV-element `--' means premature end of options.
** Skip it like a null option,
** then exchange with previous non-options as if it were an option,
** then skip everything else like a non-option.
*/

void	option_premature_end(int argc, char **argv, t_option_data *d)
{
	d->optind++;
	if (d->private_first_nonopt != d->private_last_nonopt
		&& d->private_last_nonopt != d->optind)
		option_exchange((char **)argv, d);
	else if (d->private_first_nonopt == d->private_last_nonopt)
		d->private_first_nonopt = d->optind;
	d->private_last_nonopt = argc;
	d->optind = argc;
}

/*
** If we have done all the ARGV-elements, stop the scan
** and back over any non-options that we skipped and permuted.
** Set the next-arg-index to point at the non-options
** that we previously skipped, so the caller will digest them.
*/

int		option_handle_reach_end(t_option_data *d)
{
	if (d->private_first_nonopt != d->private_last_nonopt)
		d->optind = d->private_first_nonopt;
	return (-1);
}

/*
** If we have come to a non-option and did not permute it,
** either stop the scan or describe it to the caller and pass it by.
*/

int		option_handle_reach_nonoption(char **argv, t_option_data *d)
{
	if (d->private_ordering == REQUIRE_ORDER)
		return (-1);
	d->optarg = argv[d->optind++];
	return (1);
}

/*
** Advance to the next ARGV-element.
*/

int		option_advance_to_next_argv_element(
	int argc, char **argv, t_option_data *d)
{
	if (0 == d->private_nextchar || 0 == *d->private_nextchar)
	{
		option_check_nonopt_values(d);
		if (d->private_ordering == PERMUTE)
			option_permute_prepare(argc, argv, d);
		if (d->optind != argc && !option_ft_strcmp(argv[d->optind], "--"))
			option_premature_end(argc, argv, d);
		if (d->optind == argc)
			return (option_handle_reach_end(d));
		if (NONOPTION_P)
			return (option_handle_reach_nonoption(argv, d));
		d->private_nextchar = (argv[d->optind] + 1
			+ (d->longopts != 0 && argv[d->optind][1] == '-'));
	}
	return (1);
}
