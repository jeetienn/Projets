/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 02:33:26 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 00:18:59 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dest_len;
	unsigned int	src_len;

	i = 0;
	j = 0;
	while (src[i])
		i ++;
	src_len = i;
	i = 0;
	while (dest[j])
		j ++;
	dest_len = j;
	if (dest_len >= size)
		return (size + src_len);
	while (i < (size - dest_len - 1) && src[i])
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	j = 0;
	return (dest_len + src_len);
}

// int main()
// {
// char s1[30]="aa";
// char s2[]="bb";
// 	printf("%d",ft_strlcat(s1,s2,15));
// 	printf ("%s",s1);
// char s3[30]="aa";
// char s4[]="bb";
// printf("%zu",strlcat(s3,s4,15));
// 	printf ("%s",s3);
// }
// The strlcat() function appends the NUL-terminated
// string src to the end of dst.
// It will append at most size - strlen(dst) - 1 bytes,
// NUL-termi‐nating the result.
// strlcat() functions return the total
// length of the string it tried to create.
// That means the initial length of dst plus
// the length of src.
// While this may seem somewhat confusing, it was done to make
// truncation detection simple.

// compiler cc ft_srlcat.c -lbsd
