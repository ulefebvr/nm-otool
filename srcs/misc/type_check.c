/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:45 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:45 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>

int						misc_is_macho_file(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM
		|| magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int						misc_is_fat(uint32_t magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM
		|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64);
}
