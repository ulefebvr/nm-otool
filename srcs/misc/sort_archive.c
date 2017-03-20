/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_archive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:21:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:21:39 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "misc.h"

static void			decalage(t_archive **ar, uint32_t i, uint32_t n)
{
	free(ar[i]);
	while (i < n - 1)
	{
		ar[i] = ar[i + 1];
		i++;
	}
}

static void			remove_duplicate(t_archive **ar, uint32_t *size)
{
	uint32_t		i;

	i = 0;
	while (i < *size - 1)
	{
		if (ar[i]->offset == ar[i + 1]->offset)
		{
			decalage(ar, i, *size);
			--*size;
		}
		else
		{
			i++;
		}
	}
}

void				sort(t_archive **ar, uint32_t *size)
{
	uint32_t		i;
	uint32_t		j;
	t_archive		*tmp;

	i = 0;
	j = 0;
	while (i < *size)
	{
		j = i + 1;
		while (j < *size)
		{
			if (ar[i]->offset > ar[j]->offset)
			{
				tmp = ar[i];
				ar[i] = ar[j];
				ar[j] = tmp;
			}
			j++;
		}
		i++;
	}
	remove_duplicate(ar, size);
}
