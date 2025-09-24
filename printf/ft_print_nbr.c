#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int		len;
	char	*nb;

	len = 0;
	nb = ft_itoa(n);
	len = ft_printstr(nb);
	free(nb);
	return (len);
}