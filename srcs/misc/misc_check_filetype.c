#include <stdint.h>
#include <mach-o/loader.h>

void misc_check_filetype(uint32_t magic, int *filetype)
{
	*filetype = (magic == MH_MAGIC) ? 8 : 16;
}