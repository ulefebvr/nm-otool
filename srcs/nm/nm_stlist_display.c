#include "nm.h"
#include "libft.h"

static int		ft_nbrlen_base(uint64_t i, int base)
{
	return ((i < (uint64_t)base) ? 1 : 1 + ft_nbrlen_base(i / base, base));
}

static int		ft_putunbr_base(uint64_t i, int base, int capitals)
{
	char				*str;
	int					ret;

	ret = 0;
	str = "0123456789abcdef0123456789ABCDEF";
	if (i < (uint64_t)base)
		write(1, str + (i + capitals), 1);
	else
	{
		ret += ft_putunbr_base(i / base, base, capitals);
		write(1, str + ((i % base) + capitals), 1);
	}
	return (1 + ret);
}

static void		ft_print_value(
	t_symtab *stlist, uint64_t value, int type, int base)
{
	if (stlist->value != 0)
	{
		write(1, "0000000000000000", type - ft_nbrlen_base(value, base));
		ft_putunbr_base(value, base, 0);
	}
	else
	{
		write(1, "                ", type);
	}
}

void			nm_stlist_display(t_symtab *stlist, t_ofile *ofile, int options)
{
	while (stlist)
	{
		if ((options & OPT_G) // creer define pour checker si global
			|| (options & OPT_LU && !IS_UNDEF(stlist->type))
			|| (options & OPT_BU && IS_UNDEF(stlist->type))) 
		{
			stlist = stlist->next;
			continue ;
		}
		ft_print_value(stlist, stlist->value, ofile->filetype, 16);
		ft_print(" %c %s\n", stlist->type, stlist->name);
		stlist = stlist->next;
	}
}
