/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 20:42:39 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:10:12 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int counter;

	counter = ft_strlen(s);
	while (s[counter] || s[counter] == '\0')
	{
		if (s[counter] == (unsigned char)c)
			return ((char*)&s[counter]);
		if (counter == 0)
			break ;
		counter--;
	}
	return (NULL);
}
