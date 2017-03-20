/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_check_filetype.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:33 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:34 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <mach-o/loader.h>

void	misc_check_filetype(uint32_t magic, int *filetype)
{
	*filetype = (magic == MH_MAGIC) ? 8 : 16;
}
