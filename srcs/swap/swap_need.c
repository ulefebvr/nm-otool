#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "misc.h"

void				misc_check_swap_need(uint32_t magic, char *swap)
{
	int				value;

	value = (magic == MH_CIGAM || magic == MH_CIGAM_64
		|| magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	*swap = value;
}
