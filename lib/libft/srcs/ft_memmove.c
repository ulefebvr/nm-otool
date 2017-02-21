/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:37:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:54 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*tmp;
	unsigned int	counter;

	counter = 0;
	tmp = malloc(sizeof(*src) * n);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, src, n);
	while (counter < n)
	{
		((char *)dest)[counter] = tmp[counter];
		counter++;
	}
	free(tmp);
	return (dest);
}
