/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:19:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:19:42 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "misc.h"
#include "libft.h"

#include "mapfile.h"

static long long	get_file_size(int fd)
{
	struct stat		buf;

	return ((fstat(fd, &buf) < 0) ? -1 : buf.st_size);
}

static void			release_data(t_ofile *ofile)
{
	if (ofile)
	{
		if (ofile->ptr != 0)
			munmap(ofile->ptr, ofile->filesize);
		free(ofile);
	}
}

static int			check_further(char *fname, void *faddr, size_t fsize)
{
	int				ret;
	t_mapfile		*mapfile;

	ret = 0;
	mapfile = map_file_from_mem(NULL, fname, faddr, fsize);
	if (NULL != mapfile)
	{
		map_release(mapfile);
		ret = 1;
	}
	return (ret);
}

t_ofile				*mapfile(char *fname)
{
	int				fd;
	t_ofile			*ofile;

	fd = 0;
	if ((ofile = (t_ofile *)ft_memalloc(sizeof(t_ofile))) == 0)
		ft_fdprint(2, "Error on malloc struct s_ofile\n");
	else if ((fd = open(fname, O_RDONLY)) == -1)
		ft_fdprint(2, "Open has failed on %s file\n", fname);
	else if ((long long int)(ofile->filesize = get_file_size(fd)) < 0)
		ft_fdprint(2, "Getting filesize of %s file failed\n", fname);
	else if ((ofile->ptr = mmap(0, ofile->filesize, PROT_READ, MAP_PRIVATE, fd,\
			0)) == MAP_FAILED)
		ft_fdprint(2, "The mapping of file %s has failed\n", fname);
	else if (!check_further(fname, ofile->ptr, ofile->filesize))
		ft_fdprint(2, "Parse error on file %s\n", fname);
	else
	{
		ofile->filename = fname;
		close(fd);
		return (ofile);
	}
	close(fd);
	release_data(ofile);
	return (0);
}

void				unmapfile(t_ofile *ofile)
{
	release_data(ofile);
}
