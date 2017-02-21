/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 11:45:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2014/11/05 11:45:59 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;

	a = ft_strlen(dst);
	b = 0;
	c = a + ft_strlen(src);
	d = size - a - 1;
	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + size);
	else if (ft_strlen(dst) < size)
	{
		while (src[b] && b < d)
			dst[a++] = src[b++];
		dst[a] = '\0';
	}
	return (c);
}
