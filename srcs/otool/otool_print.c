/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 10:24:18 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/03/20 10:24:19 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>

#include "libft.h"
#include "otool.h"
#include "swap.h"

static int		ft_nbrlen_base(uint64_t i, int base)
{
	return ((i < (uint64_t)base) ? 1 : 1 + ft_nbrlen_base(i / base, base));
}

static int		ft_putunbr_base(int padding, uint64_t i, int base, int capitals)
{
	char				*str;
	int					ret;

	ret = 0;
	str = "0123456789abcdef0123456789ABCDEF";
	write(1, "0000000000000000", padding - ft_nbrlen_base(i, 16));
	if (i < (uint64_t)base)
		write(1, str + (i + capitals), 1);
	else
	{
		ret += ft_putunbr_base(0, i / base, base, capitals);
		write(1, str + ((i % base) + capitals), 1);
	}
	return (1 + ret);
}

static void		print32(t_otool *otool, void *start, uint32_t size, char swap)
{
	void			*ptr;
	t_s32			*sect;
	uint64_t		start_value;

	ptr = start;
	sect = (t_s32 *)otool->section;
	start_value = (uint64_t)swap_uint32_t(sect->addr + (ptr - start), swap);
	ft_print("Contents of (%s,%s) section", sect->segname, sect->sectname);
	while (size--)
	{
		if (!((ptr - start) % 16))
		{
			write(1, "\n", 1);
			ft_putunbr_base(8, start_value + (ptr - start), 16, 0);
			write(1, "\t", 1);
		}
		ft_putunbr_base(2, (uint64_t)(unsigned char)(*(char *)ptr), 16, 0);
		ptr++;
		if (!swap || (swap && !(((ptr - start)) % 4)))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

static void		print64(t_otool *otool, void *start, uint64_t size, char swap)
{
	void			*ptr;
	t_s64			*sect;
	uint64_t		start_value;

	ptr = start;
	sect = (t_s64 *)otool->section;
	start_value = swap_uint64_t(sect->addr + (ptr - start), swap);
	ft_print("Contents of (%s,%s) section", sect->segname, sect->sectname);
	while (size--)
	{
		if (!((ptr - start) % 16))
		{
			write(1, "\n", 1);
			ft_putunbr_base(16, start_value + (ptr - start), 16, 0);
			write(1, "\t", 1);
		}
		ft_putunbr_base(2, (uint64_t)(unsigned char)(*(char *)ptr), 16, 0);
		ptr++;
		if (!swap || (swap && !(((ptr - start)) % 4)))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void			otool_print(t_otool *otool, t_ofile *ofile)
{
	if (otool->type == 32)
	{
		print32(otool, otool->section_content,
			swap_uint32_t(((t_s32 *)otool->section)->size, ofile->swap),
			ofile->swap);
	}
	else
	{
		print64(otool, otool->section_content,
			swap_uint64_t(((t_s64 *)otool->section)->size, ofile->swap),
			ofile->swap);
	}
}
