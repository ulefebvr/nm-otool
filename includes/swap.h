/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:17:30 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 18:17:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H
# define SWAP_H

# include <stdint.h>

# include "misc.h"

typedef union	u_uint32_t
{
	char		bits[4];
	uint32_t	nbr;
}				t_uint32_t;

typedef union	u_uint64_t
{
	char		bits[8];
	uint64_t	nbr;
}				t_uint64_t;

void			nm_check_swap_need(uint32_t magic, char *swap);

int				swap_int(int nbr, char swap);
uint32_t		swap_uint32_t(uint32_t nbr, char swap);
uint64_t		swap_uint64_t(uint64_t nbr, char swap);

# define SWAP32(x)		(swap_uint32_t(x, ofile->swap))
# define SWAP64(x)		(swap_uint64_t(x, ofile->swap))

#endif
