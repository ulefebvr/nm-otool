/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:59:44 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:06 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*nbr;
	int		sign;
	int		i;

	sign = (n < 0) ? -1 : 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n *= (n < 0) ? -1 : 1;
	i = ft_nbrlen(n);
	nbr = (char*)malloc(sizeof(char) * ft_nbrlen(n) + 1);
	if (!nbr)
		return (NULL);
	nbr[i] = '\0';
	if (n == 0)
		nbr[--i] = '0';
	while (n != 0)
	{
		nbr[--i] = '0' + (n % 10);
		n = n / 10;
	}
	if (sign < 0)
		nbr[--i] = '-';
	return (&nbr[i]);
}
