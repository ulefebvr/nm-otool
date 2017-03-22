/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sort_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:31:37 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:31:37 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

int				nm_sort_alphabetic(t_symtab *a, t_symtab *b)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

int				nm_sort_numerically(t_symtab *a, t_symtab *b)
{
	return (a->value > b->value);
}

int				nm_sort_symtab(t_symtab *a, t_symtab *b)
{
	return (a->n_strx > b->n_strx);
}

int				nm_sort_type(t_symtab *a, t_symtab *b)
{
	int a_upper;
	int b_upper;

	a_upper = (unsigned)(a->type - 'Z') <= (unsigned)('A' - 'Z');
	b_upper = (unsigned)(b->type - 'Z') <= (unsigned)('A' - 'Z');
	return (a_upper != b_upper && a_upper == 0);
}
