/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:29:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		if (((char*)src)[counter] == c)
			return (dest + counter + 1);
		counter++;
	}
	return (NULL);
}
