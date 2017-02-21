/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:33:37 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/11/14 16:46:11 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char				*ft_strtrim(char const *s)
{
	char *a;
	char *b;
	char *c;

	c = NULL;
	if (s && ft_strlen(s))
	{
		a = (char *)s;
		b = (char *)&(s[ft_strlen(s) - 1]);
		while ((*a == ' ' || *a == '\n' || *a == '\t') && ++a)
			;
		while ((*b == ' ' || *b == '\n' || *b == '\t') && --b && b >= a)
			;
		if (++b - a >= 0 && (c = ft_memalloc(sizeof(char) * (b - a + 1))))
			c = ft_memcpy(c, a, (b - a));
	}
	return (c);
}
