/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:21:06 by jeetienn          #+#    #+#             */
/*   Updated: 2025/02/21 20:12:41 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	ft_countwords(char const *s, char c)
{
	int	count_word;

	count_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			count_word++;
			s += ft_wordlen(s, c);
		}
		else
			s++;
	}
	return (count_word);
}

static void *ft_free_strs(char **strs)
{
    int i;

    if (!strs)
        return (NULL);

    // Libérer chaque chaîne dans strs, y compris strs[0]
    i = 0;
    while (strs[i])
    {
        free(strs[i]);  // Libérer chaque chaîne
        strs[i] = NULL; // Eviter les pointeurs pendants
        i++;
    }

    // Libérer le tableau de pointeurs lui-même
    free(strs);
    strs = NULL;

    return (NULL);
}

// Modifiez la fonction allocate_strs
char **allocate_strs(int words)
{
    char **strs;

    // Allouer words + 1 (pour le NULL final)
    strs = malloc(sizeof(char *) * (words + 1));
    if (!strs)
        return (NULL);
    
    // Initialiser tous les pointeurs à NULL
    int i = 0;
    while (i <= words)
        strs[i++] = NULL;
        
    return (strs);
}

// Modifiez ft_split
char **ft_split(char const *s, char c)
{
    char **strs;
    int i;
    int words;

    if (!s)
        return (NULL);

    words = ft_countwords(s, c);
    strs = allocate_strs(words);
    if (!strs)
        return (NULL);

    i = 0;  // Commencez à 0, pas à 1
    while (*s)
    {
        if (*s != c)
        {
            strs[i] = ft_substr(s, 0, ft_wordlen(s, c));
            if (!strs[i])
            {
                ft_free_strs(strs);
                return (NULL);
            }
            i++;
            s += ft_wordlen(s, c);
        }
        else
            s++;
    }
    
    return (strs);
}
