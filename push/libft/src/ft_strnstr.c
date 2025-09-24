/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:46:21 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:52 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while ((str[i + j] == to_find[j]) && (i + j) < len)
		{
			j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
// int main()
// {
//     char s1[]="ytjtj6u6bonjour ";
// 	char s2[]="bonlffdf ";
// 	printf("%s", ft_strnstr(s1,s2,4));
// }
// The strnstr() function locates the first occurrence of the 
// null-termi‐ated string little in the string big, where not
// more than len characters are searched.
// Characters that appear after a ‘\0’ character are not searched.
// Since the strnstr() function is a FreeBSD specific API, it
// should only be used when portability is not a concern.
