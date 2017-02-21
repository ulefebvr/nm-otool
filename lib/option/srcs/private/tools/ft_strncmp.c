/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:32 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:33 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_tools.h"

int	option_ft_strncmp(const char *p1, const char *p2, int size)
{
	if (0 == p1 || 0 == p2)
		return (-1);
	while ((unsigned char)*p1 == (unsigned char)*p2 && --size)
	{
		if ((unsigned char)*p1 == '\0')
			return ((unsigned char)*p1 - (unsigned char)*p2);
		++p1;
		++p2;
	}
	return ((unsigned char)*p1 - (unsigned char)*p2);
}
