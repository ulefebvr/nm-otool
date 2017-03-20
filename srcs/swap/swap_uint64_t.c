/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint64_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:23:25 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:23:26 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#include "libft.h"

uint64_t	swap_uint64_t(uint64_t nbr, char swap)
{
	t_uint64_t	norm;
	t_uint64_t	inv;

	if (swap)
	{
		norm.nbr = nbr;
		inv.nbr = nbr;
		inv.bits[0] = norm.bits[7];
		inv.bits[1] = norm.bits[6];
		inv.bits[2] = norm.bits[5];
		inv.bits[3] = norm.bits[4];
		inv.bits[4] = norm.bits[3];
		inv.bits[5] = norm.bits[2];
		inv.bits[6] = norm.bits[1];
		inv.bits[7] = norm.bits[0];
		return (inv.nbr);
	}
	return (nbr);
}
