/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:43:57 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:52 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char replace_odd_with_star(unsigned int i, char c) 
// {
//     if (i % 2 != 0)
//         return '*';
//     return c;
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;
	unsigned int	len_s;

	i = 0;
	len_s = ft_strlen(s);
	res = malloc((len_s + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < len_s)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

// int main()
// {
// 	const char *test ="irgeuirhguiehruig";
// 	char	*res = ft_strmapi(test, replace_odd_with_star);
// 	printf("%s\n",res);
// }
// Apply the function 'f' to each character of the string 's',
//  passing its index as the first argument and the
//   character itself as the second argument.
