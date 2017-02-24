#ifndef OTOOL_H
# define OTOOL_H

#include "misc.h"

typedef
struct segment_command		t_sc32;
typedef
struct segment_command_64	t_sc64;

typedef
struct section				t_s32;
typedef
struct section_64			t_s64;

typedef
struct fat_header			t_fh;
typedef
struct fat_arch				t_arch32;
typedef
struct fat_arch_64			t_arch64;


typedef struct				s_otool
{
	void					*archs;
	void					*ranlibs;
	void					*segment;
	void					*section;
	void					*section_content;
	int						type;
}							t_otool;

void			process_otool(t_ofile *ofile);
int				otool_gather_information(t_otool *otool, t_ofile *ofile);
int				otool_info_macho(uint32_t magic, t_otool *otool, t_ofile *ofile);
int				otool_info_fat(uint32_t magic, t_otool *otool, t_ofile *ofile);
int				otool_info_ar(t_ofile *ofile);

void			otool_print(t_otool *otool);

#endif