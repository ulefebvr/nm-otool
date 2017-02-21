/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:44:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2014/11/07 17:44:28 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_xcolums(char const *s, char c)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			a++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (a);
}

char	**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	y;
	unsigned int	len;

	y = 0;
	i = 0;
	if (!s)
		return (NULL);
	tab = (char**)malloc(sizeof(*tab) * (ft_xcolums(s, c) + 1));
	if (!tab)
		return (NULL);
	tab[ft_xcolums(s, c)] = 0;
	while (s[i])
	{
		len = 0;
		i = (s[i] == c) ? i + 1 : i;
		while (s[i] && s[i] != c && s[i++])
			len++;
		if (s[i - len] && s[i - len] != c)
			tab[y++] = ft_strsub(s, i - len, len);
	}
	return (tab);
}
