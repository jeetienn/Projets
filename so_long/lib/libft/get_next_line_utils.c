/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:53:31 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:53:34 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		++s;
	if (*s != '\0' || c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
		*(char *)dest++ = *(char *)src++;
	return ((void *)((char *)dest - i));
}

size_t	ft_strlengnl(const char *s)
{
	const char	*org = s;

	while (*s)
		++s;
	return (s - org);
}

void	ft_strcat(char **dst_ptr, const char *src)
{
	size_t	dst_len;
	size_t	src_len;
	char	*ans;

	dst_len = ft_strlengnl(*dst_ptr);
	src_len = ft_strlengnl(src);
	ans = malloc(dst_len + src_len + 1);
	if (ans)
	{
		ft_memcpy(ans, *dst_ptr, dst_len);
		ft_memcpy(ans + dst_len, src, src_len);
		ans[dst_len + src_len] = '\0';
	}
	free(*dst_ptr);
	*dst_ptr = ans;
}
