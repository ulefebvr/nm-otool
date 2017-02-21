/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:12:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2014/11/04 10:12:08 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		a;

	a = 0;
	str = NULL;
	if (s1 && (str = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 1))))
	{
		while (s1[a])
		{
			str[a] = s1[a];
			a++;
		}
		str[a] = '\0';
		return (str);
	}
	else
		return (NULL);
}
