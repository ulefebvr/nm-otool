#ifndef MAP_FILE_H
# define MAP_FILE_H

# include "misc.h"

# include "mach-o/loader.h"

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
struct symtab_command	t_symtab;

typedef
struct fat_header	t_fh;

typedef
struct fat_arch	t_fa32;

typedef
struct fat_arch_64	t_fa64;

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
	t_symtab		*macho_symtab;
\
	t_subtype		fat_subtype;
	char			fat_swap;
	t_fh			fat_header;
	t_fa32			fat_ah_32;
	t_fa64			fat_ah_64;
}					t_mapfile;
 
t_ofile				*mapfile(char *fname);
void				unmapfile(t_ofile *ofile);

t_mapfile			*map_file_from_mem(
	t_mapfile *map_arg, char *file_name, void *file_addr, size_t file_size);

t_mapfile			*map_release(t_mapfile *map);
t_mapfile			*map_appropriate(t_mapfile *map);

#endif
