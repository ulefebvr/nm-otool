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

int		ft_strcmp(const char *s1, const char *s2)
{
	int counter;

	counter = 0;
	while (s1[counter] == s2[counter] && s1[counter])
		counter++;
	return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
}
