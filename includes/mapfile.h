#ifndef MAP_FILE_H
# define MAP_FILE_H

# include "misc.h"

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

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

typedef
struct fat_header	t_fh;

typedef
struct fat_arch	t_fa32;

typedef
struct fat_arch_64	t_fa64;

typedef
struct ar_hdr	t_ar;

typedef
struct ranlib	t_rl32;

typedef
struct ranlib_64	t_rl64;

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
	t_sytab			macho_symtab;
\
	t_subtype		fat_subtype;
	char			fat_swap;
	t_fh			fat_header;
	t_fa32			*fat_ah_32;
	t_fa64			*fat_ah_64;
\
	t_subtype		arch_subtype;
	t_ar			arch_header;
	uint32_t		arch_nranlib;
	t_rl32			*arch_rl32;
	t_rl64			*arch_rl64;
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
