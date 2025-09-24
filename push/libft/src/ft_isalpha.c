/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:44:53 by jeetienn          #+#    #+#             */
/*   Updated: 2024/10/29 19:12:34 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
// int main()
// {
// 	int c ='Z';
// 	int d ='*';
// 	printf("%d\n",ft_isalpha(c));
// 	printf("%d\n",ft_isalpha(d));
//     printf("%d\n",isalpha(c));
// 	printf("%d\n",isalpha(d));
// }