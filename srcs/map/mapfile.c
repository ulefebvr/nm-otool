#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "misc.h"
#include "libft.h"

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

t_ofile				*mapfile(char *fname)
{
	int				fd;
	t_ofile			*ofile;

	if ((ofile = (t_ofile *)ft_memalloc(sizeof(t_ofile))) == 0)
		ft_fdprint(2, "Error on malloc struct s_ofile\n");
	else if ((fd = open(fname, O_RDONLY)) == -1)
		ft_fdprint(2, "Open has failed on %s file\n", fname);
	else if ((long long int)(ofile->filesize = get_file_size(fd)) < 0)
		ft_fdprint(2, "Getting filesize of %s file failed\n", fname);
	else if ((ofile->ptr = mmap(0, ofile->filesize, PROT_READ, MAP_PRIVATE, fd,\
			 0)) == MAP_FAILED)
		ft_fdprint(2, "The mapping of file %s has failed\n", fname);
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
