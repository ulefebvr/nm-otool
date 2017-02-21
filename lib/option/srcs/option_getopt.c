/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_getopt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:50:55 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:50:55 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"

int	option_getopt(t_arguments *args, const char *optstring)
{
	return (private_option_getopt(
		args, &((t_option_arguments){optstring, 0, 0}), 0));
}
