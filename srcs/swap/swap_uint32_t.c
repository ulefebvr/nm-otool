#include "swap.h"

#include "libft.h"

uint32_t swap_uint32_t(uint32_t nbr, char swap)
{
	union			u_uint32_t
	{
		char		bits[4];
		uint32_t	nbr;
	} norm, inv;

	if (swap)
	{
		norm.nbr = nbr;
		inv.nbr = nbr;
		inv.bits[0] = norm.bits[3];
		inv.bits[1] = norm.bits[2];
		inv.bits[2] = norm.bits[1];
		inv.bits[3] = norm.bits[0];
		return (inv.nbr);
	}
	return (nbr);
}