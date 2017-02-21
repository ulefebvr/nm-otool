/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:49:03 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		counter;

	counter = 0;
	if (!s || !f)
		return (NULL);
	str = ft_strnew(ft_strlen(s));
	while (s[counter])
	{
		str[counter] = f(s[counter]);
		counter++;
	}
	str[counter] = '\0';
	return (str);
}
