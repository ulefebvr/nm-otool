/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_membername.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:28 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "misc.h"

char	*get_membername(t_ofile *ofile)
{
	t_archive	*ar;
	char		*membername;

	ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint32_t));
	membername = ar->member_name;
	free(ar);
	return (membername);
}
