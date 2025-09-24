/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:50:14 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 18:50:18 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
		{
			return ((void *) &str[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// const char str1[]="aaaaaabaaaaaaaaaaa";
// printf("%p\n", memchr(str1,'b',3));
// printf("%p\n", ft_memchr(str1,'b',3));

// printf("%p\n", memchr(str1,'b',12));
// printf("%p\n", ft_memchr(str1,'b',12));
// }
