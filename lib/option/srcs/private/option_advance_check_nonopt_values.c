/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_advance_check_nonopt_values.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:53:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/03 15:53:45 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"

/*
** Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
** moved back by the user (who may also have changed the arguments).
*/

void	option_check_nonopt_values(t_option_data *d)
{
	if (d->private_last_nonopt > d->optind)
		d->private_last_nonopt = d->optind;
	if (d->private_first_nonopt > d->optind)
		d->private_first_nonopt = d->optind;
}
