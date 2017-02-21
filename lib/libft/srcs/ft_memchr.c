/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 11:01:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:39 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int counter;

	counter = 0;
	if (!s)
		return (NULL);
	while (counter < n)
	{
		if (((char*)s)[counter] == (char)c)
			return (&((char*)s)[counter]);
		counter++;
	}
	return (NULL);
}
