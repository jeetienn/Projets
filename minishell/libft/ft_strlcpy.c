/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 02:33:48 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:52 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	src_len;

	i = 0;
	while (src[i])
		i ++;
	src_len = i;
	i = 0;
	if (size == 0)
		return (src_len);
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = '\0';
	return (src_len);
}

// int main()
// {
// char s1[30]="aa";
// char s2[]="bb";
// 	printf("%d",ft_strlcpy(s1,s2,15));
// 	printf ("%s",s1);
// char s3[30]="aa";
// char s4[]="bb";
// printf("%zu",strlcpy(s3,s4,15));
// 	printf ("%s",s3);
// }
// The strlcpy() function copies up to size - 1
// characters from the NUL-terminated string src to dst,
// NUL-terminating the result.

// compiler cc ft_srlcpy.c -lbsd