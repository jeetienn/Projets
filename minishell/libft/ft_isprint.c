/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:09:41 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 17:17:14 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
		return (1);
	else
		return (0);
}
// int main()
// {
// 	int c ='Z';
// 	int d =' ';
// 	printf("%d\n",ft_isprint(c));
// 	printf("%d\n",ft_isprint(d));
//     printf("%d\n",isprint(c));
// 	printf("%d\n",isprint(d));
// }