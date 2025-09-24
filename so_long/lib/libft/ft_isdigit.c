/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:25:23 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 23:23:40 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
// int main()
// {
// 	int c ='Z';
// 	int d ='1';
// 	printf("%d\n",ft_isdigit(c));
// 	printf("%d\n",ft_isdigit(d));
//     printf("%d\n",isdigit(c));
// 	printf("%d\n",isdigit(d));
// }