/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_stlist_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:32:09 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:32:09 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		swap(void *a, void *b, size_t size)
{
	char c;

	while (size--)
	{
		c = *(char *)a;
		*(char *)a = *(char *)b;
		*(char *)b = c;
		a++;
		b++;
	}
}

static t_symtab	*nm_sort(t_symtab *stlist, int (*fn)(t_symtab *, t_symtab *))
{
	t_symtab	*tmp;
	t_symtab	*head;

	tmp = stlist;
	head = stlist;
	while (tmp && tmp->next)
	{
		if (fn(tmp, tmp->next))
		{
			swap(tmp, tmp->next, sizeof(t_symtab) - sizeof(t_symtab *));
			tmp = head;
			continue ;
		}
		tmp = tmp->next;
	}
	return (head);
}

static t_symtab	*reverse(t_symtab *before, t_symtab *node)
{
	t_symtab	*head;

	head = node;
	if (node->next)
	{
		head = reverse(node, node->next);
	}
	node->next = before;
	return (head);
}

t_symtab		*nm_stlist_sort(t_symtab *stlist, int options)
{
	stlist = nm_sort(stlist, nm_sort_alphabetic);
	if (options & OPT_N)
	{
		stlist = nm_sort(stlist, nm_sort_numerically);
	}
	else if (options & OPT_P)
	{
		stlist = nm_sort(stlist, nm_sort_symtab);
		stlist = nm_sort(stlist, nm_sort_type);
	}
	if (options & OPT_R)
	{
		stlist = reverse(0, stlist);
	}
	return (stlist);
}
