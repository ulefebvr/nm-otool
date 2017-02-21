/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:27:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n && counter < (unsigned int)ft_strlen(src))
	{
		dst[counter] = src[counter];
		counter++;
	}
	while (counter < n)
	{
		dst[counter] = '\0';
		counter++;
	}
	return (dst);
}
