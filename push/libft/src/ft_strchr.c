/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:43:48 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:52 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

// int main()
// {
// const char str1[]="aaaaaabaaaaaaaaaaa";
// printf("%p\n", strchr(str1,'b'));
// printf("%p\n", ft_strchr(str1,'b'));
// }
// The  strchr() function returns a pointer
// to the first occurrence of the
// character c in the string s.