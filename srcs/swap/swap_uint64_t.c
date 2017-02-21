#include "swap.h"

#include "libft.h"

uint64_t swap_uint64_t(uint64_t nbr, char swap)
{
	union			u_uint64_t
	{
		char		bits[8];
		uint64_t	nbr;
	} norm, inv;

	if (swap)
	{
		norm.nbr = nbr;
		inv.nbr = nbr;
		inv.bits[0] = norm.bits[7];
		inv.bits[1] = norm.bits[6];
		inv.bits[2] = norm.bits[5];
		inv.bits[3] = norm.bits[4];
		inv.bits[4] = norm.bits[3];
		inv.bits[5] = norm.bits[2];
		inv.bits[6] = norm.bits[1];
		inv.bits[7] = norm.bits[0];
		return (inv.nbr);
	}
	return (nbr);
}