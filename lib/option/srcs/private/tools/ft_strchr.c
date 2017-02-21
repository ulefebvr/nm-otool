/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:37 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:38 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*option_ft_strchr(const char *str, char c)
{
	while (str && *str)
		if (*str == c)
			return ((char *)str);
		else
			++str;
	return (0);
}
