/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:42:04 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:06:38 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int counter;
	int number;
	int sign;

	counter = 0;
	number = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (str[counter] == ' ' || str[counter] == '\t' || str[counter] == '\n'
		|| str[counter] == '\v' || str[counter] == '\f' || str[counter] == '\r')
		counter++;
	if (str[counter] == '-' || str[counter] == '+')
		sign = (str[counter++] == '-') ? -1 : 1;
	while (str[counter])
	{
		if (str[counter] > '9' || str[counter] < '0')
			return (sign * number);
		number = number * 10 + str[counter++] - '0';
	}
	return (sign * number);
}
