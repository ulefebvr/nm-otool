/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_shortoption_treat.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:06 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:07 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"
#include "option_tools.h"

/*
** This is an option that accepts an argument optionally.
*/

void	option_treat_shortoption_arguments_optionnal(t_option_data *d)
{
	if (*d->private_nextchar != '\0')
	{
		d->optarg = d->private_nextchar;
		d->optind++;
	}
	else
		d->optarg = 0;
	d->private_nextchar = 0;
}

/*
** This is an option that requires an argument.
** If we end this ARGV-element by taking the rest as an arg,
** we must advance to the next element now.
** We already incremented `optind' once;
** increment it again when taking next ARGV-elt as argument.
*/

int		option_treat_shortoption_arguments_required(
						t_arguments *args, t_option_data *d, char c)
{
	if (*d->private_nextchar != '\0')
	{
		d->optarg = d->private_nextchar;
		d->optind++;
	}
	else if (d->optind == args->argc)
	{
		if (d->opterr)
			option_ft_fdprint(2, "%s: option requires an argument -- '%c'\n",
				args->argv[0], c);
		d->optopt = c;
		if (d->optstring[0] == ':')
			c = ':';
		else
			c = '?';
	}
	else
		d->optarg = args->argv[d->optind++];
	d->private_nextchar = 0;
	return (c);
}

int		option_treat_shortoption_arguments(
						t_arguments *args, t_option_data *d, char *temp, char c)
{
	if (temp[2] == ':')
		option_treat_shortoption_arguments_optionnal(d);
	else
		c = option_treat_shortoption_arguments_required(args, d, c);
	return (c);
}

int		option_treat_shortoption_invalid(char **argv, t_option_data *d, char c)
{
	if (d->opterr)
	{
		option_ft_fdprint(2, "%s: invalid option -- '%c'\n", argv[0], c);
	}
	d->optopt = c;
	return ('?');
}

int		option_treat_shortoption(int argc, char **argv, t_option_data *d)
{
	char c;
	char *temp;

	c = *d->private_nextchar++;
	temp = option_ft_strchr(d->optstring, c);
	if (*d->private_nextchar == '\0')
		++d->optind;
	if (0 == temp || ':' == c || ';' == c)
		return (option_treat_shortoption_invalid(argv, d, c));
	if (':' == temp[1])
		c = option_treat_shortoption_arguments(
			&(t_arguments){argc, argv, 0}, d, temp, c);
	return ((int)c);
}
