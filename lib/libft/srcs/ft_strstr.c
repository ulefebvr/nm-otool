/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:51:37 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:10:17 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *meule_de_foin, const char *aiguille)
{
	int a;
	int b;

	a = 0;
	b = 0;
	if (!aiguille)
		return ((char*)meule_de_foin);
	if (*aiguille == 0)
		return ((char*)meule_de_foin);
	while (meule_de_foin[a])
	{
		while (aiguille[b] && aiguille[b] == meule_de_foin[a + b])
			b++;
		if (aiguille[b] == '\0')
			return ((char*)&meule_de_foin[a]);
		b = 0;
		a++;
	}
	return (NULL);
}
