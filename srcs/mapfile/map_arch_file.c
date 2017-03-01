#include "mapfile.h"

t_mapfile		*map_arch_file(t_mapfile *map)
{

}

t_mapfile		*map_arch_file(t_mapfile *map)
{
	if (map_arch_get_header(map) == NULL)
		return (NULL);
}