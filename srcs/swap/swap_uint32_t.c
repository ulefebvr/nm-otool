/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint32_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:30 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#include "libft.h"

uint32_t	swap_uint32_t(uint32_t nbr, char swap)
{
	t_uint32_t	norm;
	t_uint32_t	inv;

	if (swap)
	{
		norm.nbr = nbr;
		inv.nbr = nbr;
		inv.bits[0] = norm.bits[3];
		inv.bits[1] = norm.bits[2];
		inv.bits[2] = norm.bits[1];
		inv.bits[3] = norm.bits[0];
		return (inv.nbr);
	}
	return (nbr);
}
