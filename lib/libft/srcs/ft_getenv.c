/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 11:57:40 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/11/14 17:19:24 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char **env, char *str)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if (!str || !(tmp = ft_strjoin(str, "=")))
		return (NULL);
	start = ft_strlen(tmp);
	while (env && env[++i])
	{
		if (!(ft_strncmp(env[i], tmp, start)))
		{
			free(tmp);
			len = ft_strlen(ft_strchr(env[i], '='));
			return (ft_strsub(env[i], start, len));
		}
	}
	free(tmp);
	return (NULL);
}
