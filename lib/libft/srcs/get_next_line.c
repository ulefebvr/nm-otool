/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 12:58:47 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/09 11:22:55 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	end_of_file(char **line, char **lin)
{
	if (lin && *lin && **lin)
	{
		*line = *lin;
		*lin = NULL;
		return (1);
	}
	return (0);
}

static int	read_line(int fd, char **line, char **lin)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if ((tmp = ft_strchr(buf, '\n')))
		{
			*tmp = '\0';
			if (!(*line = ft_strjoin(*lin, buf)) ||
				!(tmp = ft_strdup(tmp + 1)))
				return (-1);
			free(*lin);
			*lin = tmp;
			return (1);
		}
		if (!(tmp = ft_strjoin(*lin, buf)))
			return (-1);
		free(*lin);
		*lin = tmp;
	}
	return (end_of_file(line, lin));
}

int			get_next_line(int fd, char **line)
{
	static char		*lin;
	char			*tmp;

	if (lin)
	{
		if ((tmp = ft_strchr(lin, '\n')))
		{
			*tmp = '\0';
			if (!(*line = ft_strdup(lin)) ||
				!(tmp = ft_strdup(tmp + 1)))
				return (-1);
			free(lin);
			lin = tmp;
			return (1);
		}
	}
	else
	{
		if (!(lin = (char *)malloc((sizeof(char)))))
			return (-1);
		*lin = '\0';
	}
	return (read_line(fd, line, &lin));
}
