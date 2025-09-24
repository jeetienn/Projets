/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:27:28 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 20:17:12 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void copy_n(char *result, int len, int n)
{
    int is_negative;
    
    is_negative = (n < 0);
    if (is_negative)
    {
        while (len > 0)
        {
            result[len] = '0';
            len--;
        }
        len = count_len(n) - 1;
    }
    
    while (n != 0)
    {
        if (is_negative)
        {
            result[len] = '0' + -(n % 10);
        }
        else
        {
            result[len] = '0' + (n % 10);
        }
        len--;
        n = n / 10;
    }
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = count_len(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	len--;
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (n < 0)
		result[0] = '-';
	copy_n(result, len, n);
	return (result);
}
// int main()
// {
// 	int n = -2147483648;
// 	printf("%s\n",ft_itoa(n));
// }