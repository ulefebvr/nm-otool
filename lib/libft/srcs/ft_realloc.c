/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 21:57:52 by ulefebvr          #+#    #+#             */
/*   Updated: 2014/11/16 21:57:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, unsigned int n)
{
	char	*cpy;
	int		counter;

	cpy = (char*)malloc((sizeof(char) * (ft_strlen(str) + n)));
	if (!cpy)
		return (NULL);
	if (!str)
		return (cpy);
	counter = 0;
	while (str[counter])
	{
		cpy[counter] = str[counter];
		counter++;
	}
	cpy[counter] = '\0';
	free(str);
	return (cpy);
}
