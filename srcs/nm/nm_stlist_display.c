/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_stlist_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:31:57 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:31:57 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

#include <mach-o/stab.h>

static int		ft_nbrlen_base(uint64_t i, int base)
{
	return ((i < (uint64_t)base) ? 1 : 1 + ft_nbrlen_base(i / base, base));
}

static int		ft_putunbr_base(uint64_t i, int base, int capitals)
{
	char				*str;
	int					ret;

	ret = 0;
	str = "0123456789abcdef0123456789ABCDEF";
	if (i < (uint64_t)base)
		write(1, str + (i + capitals), 1);
	else
	{
		ret += ft_putunbr_base(i / base, base, capitals);
		write(1, str + ((i % base) + capitals), 1);
	}
	return (1 + ret);
}

static void		ft_print_value(
	t_symtab *stlist, int options, int type, int base)
{
	if (stlist->value != 0 || ((options & AR_T) && stlist->type == 'T')
		|| (stlist->value == 0 && (stlist->type == 'T' || stlist->type == 't')))
	{
		write(1, "0000000000000000",
			type - ft_nbrlen_base(stlist->value, base));
		ft_putunbr_base(stlist->value, base, 0);
	}
	else
	{
		write(1, "                ", type);
	}
}

void			nm_stlist_display(t_symtab *stlist, t_ofile *ofile, int options)
{
	while (stlist)
	{
		if (!ft_strlen(stlist->name)
			|| stlist->type == 'u'
			|| ((options & OPT_G) 
				&& !((unsigned)(stlist->type - 'A') <= ('Z' - 'A')))
			|| stlist->type == 0
			|| (options & OPT_LU && !IS_UNDEF(stlist->type))
			|| (options & OPT_BU && IS_UNDEF(stlist->type))
			|| (stlist->type == '-' && !(options & OPT_A)))
		{
			stlist = stlist->next;
			continue ;
		}
		if (!(options & OPT_J) && !(options & OPT_LU))
		{
			ft_print_value(stlist, options, ofile->filetype,
				(options & OPT_X) ? 10 : 16);
			ft_print(" %c ", stlist->type);
		}
		ft_print("%s\n", stlist->name);
		stlist = stlist->next;
	}
}
