/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:09:11 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 20:16:01 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// "nemb"  : n elements of "size" bytes
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	mem = malloc (nmemb * size);
	if (!mem)
		return (NULL);
	while (i < nmemb * size)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}

// int main()
// {
// 	int i;
// 	unsigned char *result = (unsigned char *)ft_calloc(3, 4);

// 	i = 0;
// 	while(i<3*4)
// 	{
// 		printf("%d ", result[i]);
// 		i++;
// 	}
// 	printf("\n");
// }