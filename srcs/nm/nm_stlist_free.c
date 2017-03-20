/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_stlist_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:32:04 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 13:32:05 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "nm.h"

void			nm_stlist_free(t_symtab *list)
{
	t_symtab	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
