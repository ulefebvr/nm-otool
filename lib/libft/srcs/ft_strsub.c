/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:24:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:10:21 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	counter;

	if (!s)
		return (NULL);
	str = (char*)malloc(sizeof(char) * len + 1);
	counter = 0;
	if (!str)
		return (NULL);
	while (s[counter + start] && counter < len)
	{
		str[counter] = s[counter + start];
		counter++;
	}
	str[counter] = '\0';
	return (str);
}
