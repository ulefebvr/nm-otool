/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_them_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:33:27 by rclanget          #+#    #+#             */
/*   Updated: 2016/11/14 16:46:22 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

void	ft_free_them_all(int nb, ...)
{
	va_list		list;
	void		*target;

	va_start(list, nb);
	while (nb-- > 0)
	{
		if ((target = va_arg(list, void **)))
		{
			free(*(char **)target);
			*(char **)target = NULL;
		}
	}
	va_end(list);
}
