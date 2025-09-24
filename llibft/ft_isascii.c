/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:00:52 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 18:46:45 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
// int main()
// {
// 	int c ='8';
// 	int d ='*';
// 	printf("%d\n",ft_isascii(c));
// 	printf("%d\n",ft_isascii(d));
//     printf("%d\n",isascii(c));
// 	printf("%d\n",isascii(d));
// }