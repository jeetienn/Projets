/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:50:26 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 18:41:34 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
	|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
// int main()
// {
// 	int c ='*';
// 	int d ='1';
// 	printf("%d\n",ft_isalnum(c));
// 	printf("%d\n",ft_isalnum(d));
//     printf("%d\n",isalnum(c));
// 	printf("%d\n",isalnum(d));
// }