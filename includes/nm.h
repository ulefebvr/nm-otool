/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 18:13:25 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 18:13:26 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdint.h>
# include <mach-o/nlist.h>

# include "misc.h"

# define ERR_USAGE		"./ft_nm  [ -agnpruUxj ]"
# define NM_OPTIONS		"npraguUxjh"

# define IS_UNDEF(x)	(x == 'U' || x == 'u')

# define OPT_N			0x001
# define OPT_P			0x002
# define OPT_R			0x004
# define OPT_A			0x008
# define OPT_G			0x010
# define OPT_LU			0x020
# define OPT_BU			0x040
# define OPT_X			0x080
# define OPT_J			0x100
# define AR_T			0x200

typedef struct mach_header		t_mh;
typedef struct load_command		t_lc;
typedef struct symtab_command	t_stc;
typedef struct fat_header		t_fh;
typedef struct fat_arch			t_arch32;
typedef struct fat_arch_64		t_arch64;

typedef struct			s_symtab
{
	uint32_t			n_strx;
	uint8_t				n_type;
	uint64_t			value;
	char				type;
	char				*name;
	uint8_t				n_sect;
	char				*pathname;
	struct s_symtab		*next;
}						t_symtab;

t_symtab				*nm_load_macho_command(uint32_t magic, t_ofile *ofile);
t_symtab				*nm_load_fat_command(
							uint32_t magic, t_ofile *ofile, int opt);
t_symtab				*nm_load_archive_command(t_ofile *ofile, int opt);
t_symtab				*nm_get_stlist(t_ofile *ofile, int ac, int opt);
t_symtab				*add_new_stlist(t_symtab *tail, char *stringtable,
							struct nlist info, t_ofile *ofile);
t_symtab				*add_new_stlist_64(t_symtab *tail, char *stringtable,
							struct nlist_64 info, t_ofile *ofile);

t_symtab				*nm_stlist_sort(t_symtab *stlist, int options);
int						nm_sort_alphabetic(t_symtab *a, t_symtab *b);
int						nm_sort_numerically(t_symtab *a, t_symtab *b);
int						nm_sort_symtab(t_symtab *a, t_symtab *b);
int						nm_sort_type(t_symtab *a, t_symtab *b);

void					nm_stlist_display(t_symtab *stlist, t_ofile *ofile,
							int option);

void					nm_stlist_free(t_symtab *list);

#endif
