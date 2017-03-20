/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ar_hdr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:19 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:19 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include "libft.h"

t_archive				*get_ar_header(void *ptr, uint32_t offset, size_t size)
{
	t_archive			*ar;
	int					n;

	ar = ft_memalloc(S_AR_HDR);
	ar->header = (struct ar_hdr *)((char *)ptr + offset);
	if ((n = ft_atoi(ar->header->ar_name + 3)) == 0)
		ar->member_name = ar->member_name + 3;
	else
		ar->member_name = (char *)ar->header + S_AR_HDR;
	ar->offset = offset;
	if (size == sizeof(uint32_t))
		ar->size = (uint64_t)(*(uint32_t *)((char *)ar->header + S_AR_HDR + n));
	else
		ar->size = *(uint64_t *)((char *)ar->header + S_AR_HDR + n);
	ar->object = ((char *)ar->header + S_AR_HDR + n);
	ar->ranlibs = (char *)ar->object + size;
	return (ar);
}
