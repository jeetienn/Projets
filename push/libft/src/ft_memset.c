/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:55:14 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 17:19:06 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// The  memset()  function  fills  the  first  n  bytes of the memory area
// pointed to by s with the constant byte c.

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
// int main()
// {
// char str[] ="AAAAAAAA";
// memset(str, 'X', 4);

// printf ("%s\n",str);
// printf("%p\n",memset(str, 'X', 4));

// char str2[] ="AAAAAAAA";
// ft_memset(str2, 'X', 4);

// printf ("%s\n",str2);
// printf("%p\n",ft_memset(str2, 'X', 4));
// }