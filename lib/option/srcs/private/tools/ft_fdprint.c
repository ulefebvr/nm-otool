/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:42 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:42 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "option_tools.h"

static int		ft_putstr_fd(char *str, int fd)
{
	return (write(fd, str, option_ft_strlen(str)));
}

static int		ft_putchar_fd(int c, int fd)
{
	return (write(fd, (char *)&c, 1));
}

static void		run_print(int fd, const char *fmt, va_list list)
{
	while (*fmt)
	{
		if (*fmt == '%' && fmt++)
		{
			if (*fmt == 's')
				ft_putstr_fd(va_arg(list, char *), fd);
			else if (*fmt == 'c')
				ft_putchar_fd(va_arg(list, int), fd);
			fmt++;
		}
		else
			write(fd, fmt++, 1);
	}
}

int				option_ft_fdprint(int fd, const char *fmt, ...)
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
