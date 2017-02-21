/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 10:46:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(content_size);
	if (!new->content)
		return (NULL);
	new->content = (!content) ? NULL : ft_memcpy(new->content,
														content, content_size);
	new->content_size = (!content) ? 0 : content_size;
	new->next = NULL;
	return (new);
}
