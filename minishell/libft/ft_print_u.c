/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_num(unsigned	int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa_u(unsigned int n)
{
	char	*nb;
	int		len;

	len = ft_len_num(n);
	nb = (char *)malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (0);
	nb[len] = '\0';
	while (n != 0)
	{
		nb[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (nb);
}

int	ft_print_u(unsigned int n)
{
	int		lenprint;
	char	*nb;

	lenprint = 0;
	if (n == 0)
		lenprint += write(1, "0", 1);
	else
	{
		nb = ft_itoa_u(n);
		lenprint += ft_printstr(nb);
		free(nb);
	}
	return (lenprint);
}
