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
