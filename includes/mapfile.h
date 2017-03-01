#ifndef MAP_FILE_H
# define MAP_FILE_H

# include "misc.h"

# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef enum		e_type
{
	MACHO, FAT, ARCH, UNKNOW
}					t_type;

typedef enum		e_subtype
{
	B32, B64
}					t_subtype;

typedef
struct mach_header	t_mh;

typedef
struct load_command	t_lc;

typedef
struct segment_command	t_sc32;

typedef
struct segment_command_64	t_sc64;

typedef
struct symtab_command	t_sytab;

typedef
struct section		t_s32;

typedef
struct section_64	t_s64;

typedef struct		s_mapfile
{
	char			*file_name;
	size_t			file_size;
	void			*file_addr;
	t_type			file_type;
\
	uint32_t		magic;
\
	t_subtype		macho_subtype;
	char			macho_swap;
	t_mh			macho_header;
	t_lc			*macho_lc;
	t_lc			*macho_segment;
	t_s64			*macho_sections;
	t_sytab			macho_symtab;
}					t_mapfile;

t_ofile				*mapfile(char *fname);
void				unmapfile(t_ofile *ofile);

t_mapfile			*map_file_from_mem(
	t_mapfile *map_arg, char *file_name, void *file_addr, size_t file_size);

t_mapfile			*map_release(t_mapfile *map);
t_mapfile			*map_appropriate(t_mapfile *map);

t_mapfile			*map_macho_file(t_mapfile *map);

t_mapfile			*map_fat_file(t_mapfile *map);
t_mapfile			*map_arch_file(t_mapfile *map);


#endif
