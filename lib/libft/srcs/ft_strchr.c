/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:49:02 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:08:49 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int counter;

	counter = 0;
	if (!s)
		return (NULL);
	while (s[counter])
	{
		if (((char*)s)[counter] == (char)c)
			return ((char*)&s[counter]);
		counter++;
	}
	if (((char*)s)[counter] == (char)c)
		return ((char*)&s[counter]);
	return (NULL);
}
