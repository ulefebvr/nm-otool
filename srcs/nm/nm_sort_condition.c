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
