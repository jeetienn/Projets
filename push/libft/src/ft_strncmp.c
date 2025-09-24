/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:20:22 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 17:54:46 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char s1[] = "aaaaaaaaaaaaaaaa";
// 	char s2[] = "aaaa1aaa";
// 	size_t n = 6;

// 	printf("%d\n",strncmp(s1,s2,n));
// 	printf("%d\n",ft_strncmp(s1,s2,n));

// }
