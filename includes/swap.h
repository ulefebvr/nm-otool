#ifndef SWAP_H
# define SWAP_H

# include <stdint.h>

# include "misc.h"

union			u_uint32_t
{
	char		bits[4];
	uint32_t	nbr;
}				t_uint32_t;

void			nm_check_swap_need(uint32_t magic, char *swap);

int				swap_int(int nbr, char swap);
uint32_t		swap_uint32_t(uint32_t nbr, char swap);
uint64_t		swap_uint64_t(uint64_t nbr, char swap);

#endif