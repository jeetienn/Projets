/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_redirect_part(char *result, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(result, part);
	free(part);
	free(result);
	return (tmp);
}

char	*extract_redirect_filename(char *str, int *i)
{
	char	*result;
	char	*part;
	int		start;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*i] && !is_operator(str, *i))
	{
		while (is_whitespace(str[*i]))
			(*i)++;
		if (!str[*i] || is_operator(str, *i))
			break ;
		start = *i;
		while (str[*i] && !is_whitespace(str[*i]) && !is_operator(str, *i))
			(*i)++;
		part = ft_strndup(str + start, *i - start);
		if (!part)
			return (free(result), NULL);
		result = join_redirect_part(result, part);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*extract_word(char *str, int *i, t_env *env, int *exit_status)
{
	if (str[*i] == '$' && str[*i + 1] && !is_whitespace(str[*i + 1])
		&& str[*i + 1] != '\'' && str[*i + 1] != '"')
		return (extract_env_variable(str, i, env, exit_status));
	if (str[*i] == '\'')
		return (extract_single_quoted(str, i));
	if (str[*i] == '"')
		return (extract_double_quoted(str, i, env, exit_status));
	return (extract_plain_word(str, i));
}

t_token	*extract_operator(char *str, int *i)
{
	if (str[*i] == '|')
		return ((*i)++, create_token(TOKEN_PIPE, "|"));
	if (str[*i] == '<' && str[*i + 1] == '<')
		return ((*i) += 2, create_token(TOKEN_HEREDOC, "<<"));
	if (str[*i] == '<')
		return ((*i)++, create_token(TOKEN_REDIRECT_IN, "<"));
	if (str[*i] == '>' && str[*i + 1] == '>')
		return ((*i) += 2, create_token(TOKEN_REDIRECT_APPEND, ">>"));
	if (str[*i] == '>')
		return ((*i)++, create_token(TOKEN_REDIRECT_OUT, ">"));
	return (NULL);
}
