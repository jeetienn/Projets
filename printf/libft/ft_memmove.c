/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:53:19 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 18:09:21 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Check if the address of dest is greater than the address
	// of src then replace backward to avoid overlapping.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*dst;

	source = (unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			dst[n] = source[n];
		}
	}
	else
	{
		ft_memcpy(dst, src, n);
	}
	return (dest);
}
// int main()
// {
// 	char dest[] = "aaaaaaaaaaaaaaaaaaaaaa";
// 	char src[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
// 	size_t n = 4;
// 	printf("%p\n",memmove(dest,src,n));
// 	printf ("%s\n",dest);

// 	char dest2[] = "aaaaaaaaaaaaaaaaaaaaaa";

// 	char src2[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
// 	size_t n2 = 4;
// 	printf("%p\n",ft_memmove(dest2,src2,n2));
// 	printf ("%s\n",dest2);
// }