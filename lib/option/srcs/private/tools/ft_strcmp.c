/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:39 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:40 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	option_ft_strcmp(char *p1, char *p2)
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
