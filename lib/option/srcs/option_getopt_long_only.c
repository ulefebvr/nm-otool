/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_getopt_long_only.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:01 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:02 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"

int	option_getopt_long_only(t_arguments *args, t_option_arguments *options)
{
	return (private_option_getopt(args, options, 1));
}
