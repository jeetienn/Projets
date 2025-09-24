/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:08:14 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 18:33:36 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, int n)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
	return (s);
}
// int main()
// {
// char str[] ="AAAAAAAAaaaaaaaaaaaaaaa";
// bzero(str, 4);
// printf ("%s\n",str);

// char str2[] ="AAAAAAAA";
// ft_bzero(str2, 4);

// printf ("%s\n",str2);
// int i = 0;
// while(i<8)
// {
//     write(1,&str[i],1);
//     i++;
// }
