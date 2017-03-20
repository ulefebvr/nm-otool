/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:51 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:51 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "misc.h"

int					misc_valid_magic(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_MAGIC_64
		|| magic == MH_CIGAM || magic == MH_CIGAM_64
		|| magic == FAT_MAGIC || magic == FAT_CIGAM
		|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64);
}
