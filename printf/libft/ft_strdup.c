/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:18:27 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:16:52 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	while (s[len])
		len++;
	res = (char *)malloc((len + 1) * (sizeof (char)));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int main()
// {	char *res;
// 	char *s = "AAAAAAAA";
// 	res = ft_strdup(s);
// 	printf("%s\n",res);
// }
// The  strdup() function returns a pointer
// to a new string which is a duplicate of the
// string s.
