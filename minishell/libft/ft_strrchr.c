/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:23:26 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:15:37 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	i = 0;
	last = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = (char *)s + i;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (last);
}
// the last if (s[i] == (char)c) is in case c = '/0'
// int main()
// {
// const char str1[]="aaaaaabaaaabaaaaaaa";
// printf("%p\n", strrchr(str1,'b'));
// printf("%p\n", ft_strrchr(str1,'b'));
// }
// The strrchr() function returns a pointer to
// the last occurrence of  the character c in the string s.
