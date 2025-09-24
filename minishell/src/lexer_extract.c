/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var_value(char *key, t_env *env, int *exit_status)
{
	char	*word;

	if (ft_strcmp(key, "?") == 0)
		word = ft_itoa(*exit_status);
	else
		word = ft_strdup(get_env_value(env, key));
	return (word);
}

char	*extract_env_variable(char *str, int *i, t_env *env, int *exit_status)
{
	char	*word;
	char	*key;
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] && !is_whitespace(str[*i]) && !is_operator(str, *i)
		&& str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	key = ft_strndup(str + start, *i - start);
	if (!key)
		return (NULL);
	word = get_env_var_value(key, env, exit_status);
	free(key);
	return (word);
}

char	*extract_single_quoted(char *str, int *i)
{
	int		start;
	char	*result;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		return (NULL);
	result = ft_strndup(str + start, *i - start);
	(*i)++;
	return (result);
}

char	*extract_plain_word(char *str, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (str[*i] && !is_whitespace(str[*i]) && !is_operator(str, *i))
	{
		if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] && str[*i] != '"')
				(*i)++;
			if (str[*i] == '"')
				(*i)++;
		}
		else
			(*i)++;
	}
	result = ft_strndup(str + start, *i - start);
	return (result);
}
