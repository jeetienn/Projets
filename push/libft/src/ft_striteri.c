/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:42:03 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:20:28 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// static void replace_odd_with_star(unsigned int i, char *c) 
// {
//     if (i % 2 != 0)
//     {
//         *c = '*';
//     }
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// int main()
// {
// 	char test[] ="irgeuirhguiehruig";
// 	ft_striteri(test, replace_odd_with_star);
// 	printf("%s\n",test);
// }
// Apply the function 'f' to each character of
// the string passed as an argument, passing its index
// as the first argument. 
// Each character is passed 
// by address to 'f' to be modified if necessary.t
