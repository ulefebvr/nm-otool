/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 11:36:54 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:17:27 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		if (((unsigned char*)s1)[counter] != ((unsigned char*)s2)[counter])
		{
			return (((unsigned char*)s1)[counter]
				- ((unsigned char*)s2)[counter]);
		}
		counter++;
	}
	return (0);
}
