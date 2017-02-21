/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_preparation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:09 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:09 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"

/*
** Determine how to handle the ordering of options and nonoptions.
*/

void		option_handle_ordering(t_option_data *d)
{
	if (*d->optstring == '-')
	{
		d->private_ordering = RETURN_IN_ORDER;
		++d->optstring;
	}
	else if (*d->optstring == '+')
	{
		d->private_ordering = REQUIRE_ORDER;
		++d->optstring;
	}
	else
		d->private_ordering = PERMUTE;
}

/*
** Start processing options with ARGV-element 1 (since ARGV-element 0
** is the program name); the sequence of previously skipped
** non-option ARGV-elements is empty.
*/

const char	*option_initialize(t_option_data *d)
{
	d->optind = d->optind ? d->optind : 1;
	d->private_first_nonopt = d->optind;
	d->private_last_nonopt = d->optind;
	option_handle_ordering(d);
	d->private_initialized = 1;
	return (d->optstring);
}

void		option_preparation(t_option_data *d)
{
	d->optarg = 0;
	if (d->optind == 0 || d->private_initialized == 0)
		option_initialize(d);
	else if (*d->optstring == '-' || *d->optstring == '+')
		++d->optstring;
	if (*d->optstring == ':')
		d->opterr = 0;
}
