/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 11:26:21 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 12:14:54 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>

void		run_print(int fd, const char *fmt, va_list list)
{
	while (*fmt)
	{
		if (*fmt == '%' && fmt++)
		{
			if (*fmt == 's')
				ft_putstr_fd(va_arg(list, char *), fd);
			else if (*fmt == 'd')
				ft_putnbr_fd(va_arg(list, int), fd);
			else if (*fmt == 'c')
				ft_putchar_fd(va_arg(list, int), fd);
			fmt++;
		}
		else
			write(fd, fmt++, 1);
	}
}

int			ft_print(const char *fmt, ...)
{
	va_list		list;

	if (fmt)
	{
		va_start(list, fmt);
		run_print(1, fmt, list);
		va_end(list);
	}
	return (1);
}

int			ft_fdprint(int fd, const char *fmt, ...)
{
	va_list		list;

	if (fmt)
	{
		va_start(list, fmt);
		run_print(fd, fmt, list);
		va_end(list);
	}
	return (1);
}
