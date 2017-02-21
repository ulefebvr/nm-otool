/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/24 14:50:18 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/28 17:57:40 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_pow(int exposant)
{
	int i;

	i = 1;
	while (exposant--)
		i = i << 1;
	return (i);
}

static void	ft_option_error(char *prog, char c)
{
	char *s;

	s = prog;
	while (*prog)
		prog++;
	write(2, s, prog - s);
	write(2, ": illegal option -- ", 20);
	write(2, &c, 1);
	write(2, "\n", 1);
}

static int	ft_mark_option(char **av, const char *list, int *opt, char *str)
{
	char *s;

	s = (char *)list;
	while (*str)
	{
		list = s;
		while (*list)
		{
			if (*list == *str && (*opt |= ft_pow(list - s)))
				break ;
			list++;
		}
		if (!*list)
		{
			ft_option_error(av[0], *str);
			return (0);
		}
		str++;
	}
	return (1);
}

static int	ft_get_option(char **av, const char *list, int *option)
{
	int i;

	i = 1;
	*option = 0;
	while (av[i])
	{
		if (av[i][0] != '-')
			break ;
		if (!av[i][1] || (av[i][1] == '-' && i++))
			break ;
		if (!ft_mark_option(av, list, option, &av[i][1]))
			return (-1);
		i++;
	}
	return (i);
}

int			ft_option(int ac, char **av, const char *list, int *option)
{
	char *s;

	if (ac == 1)
		return (1);
	s = (char *)list;
	while (*list)
		list++;
	if (list - s >= 32)
		return (write(2, "Error : Too many option\n", 24) - 25);
	return (ft_get_option(av, s, option));
}
