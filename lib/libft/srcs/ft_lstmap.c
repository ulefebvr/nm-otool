/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 12:21:51 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:27 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *newone;
	t_list *begin_list;

	tmp = lst;
	if (!lst || !f)
		return (NULL);
	if (!(newone = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	newone = f(tmp);
	begin_list = newone;
	tmp = tmp->next;
	while (tmp)
	{
		newone = newone->next;
		if (!(newone = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		newone = f(tmp);
		tmp = tmp->next;
	}
	return (begin_list);
}
