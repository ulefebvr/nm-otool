/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 14:56:16 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:49 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int counter;

	counter = 0;
	if (!n)
		return (0);
	while (s1[counter] == s2[counter] && s1[counter] && counter < n - 1)
		counter++;
	return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
}
