/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:52:44 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:47 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	const unsigned char	*source;

	if (dest == NULL && src == NULL)
		return (NULL);
	dst = (unsigned char *)dest;
	source = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
// int main()
// {
// char dest1[] = "                             ";
// char str[] ="AAAAAAAAaaaaaaaaaaaaaaa";
// memcpy(dest1, str, 4);

// printf ("%s\n",dest1);

// char dest2[] = "                  ";
// char str2[] ="AAAAAAAA";
// ft_memcpy(dest2, str2, 4);

// printf ("%s\n",dest2);
// }