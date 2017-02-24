#include <stdlib.h>

#include "misc.h"

char	*get_membername(t_ofile *ofile)
{
	t_archive	*ar;
	char		*membername;

	ar = get_ar_header(ofile->ptr, SARMAG, sizeof(uint32_t));
	membername = ar->member_name;
	free(ar);
	return (membername);
}
