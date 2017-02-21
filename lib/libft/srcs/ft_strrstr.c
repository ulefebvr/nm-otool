/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:23:21 by rclanget          #+#    #+#             */
/*   Updated: 2016/12/13 14:53:08 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *meule_de_foin, const char *aiguille)
{
	int a;
	int len_aiguille;

	a = ft_strlen(meule_de_foin) - 1;
	len_aiguille = ft_strlen(aiguille);
	if (!aiguille || *aiguille == 0)
		return ((char*)meule_de_foin);
	while (a >= 0)
	{
		if (!ft_strncmp(meule_de_foin + a, aiguille, len_aiguille))
			return ((char*)meule_de_foin + a);
		a--;
	}
	return (NULL);
}
