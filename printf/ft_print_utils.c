#include "ft_printf.h"

int ft_print_c(int c)
{
	write(1, &c, 1);
	return(1);
}

int ft_printstr(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return(6);
	}
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return(i);
}

int ft_percent(void)
{
	write(1, "%", 1);
	return(1);
}