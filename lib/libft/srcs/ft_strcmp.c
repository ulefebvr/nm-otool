/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:25:52 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:08:57 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *p1, const char *p2)
{
	if (0 == p1 || 0 == p2)
		return (-1);
	while ((unsigned char)*p1 == (unsigned char)*p2)
	{
		if ((unsigned char)*p1 == '\0')
			return ((unsigned char)*p1 - (unsigned char)*p2);
		++p1;
		++p2;
	}
	return ((unsigned char)*p1 - (unsigned char)*p2);
}