/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_env_in_quotes(char *str, int *i, t_lexer_context *ctx)
{
	char	*key;
	char	*value;
	int		start;

	start = ++(*i);
	while (str[*i] && !is_whitespace(str[*i]) && !is_operator(str, *i)
		&& str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	key = ft_strndup(str + start, *i - start);
	if (!key)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(*(ctx->exit_status));
	else
		value = ft_strdup(get_env_value(ctx->env, key));
	free(key);
	return (value);
}

static char	*process_escaped_char(char *str, int *i)
{
	char	*result;

	(*i)++;
	if (!str[*i])
		return (ft_strdup("\\"));
	if (str[*i] == '"' || str[*i] == '\\' || str[*i] == '$')
	{
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = str[*i];
		result[1] = '\0';
	}
	else
	{
		result = malloc(3);
		if (!result)
			return (NULL);
		result[0] = '\\';
		result[1] = str[*i];
		result[2] = '\0';
	}
	(*i)++;
	return (result);
}

static char	*process_literal_in_quotes(char *str, int *i)
{
	char	*part;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '$' && str[*i] != '\\')
		(*i)++;
	if (*i == start)
		return (ft_strdup(""));
	part = ft_strndup(str + start, *i - start);
	return (part);
}

static int	process_double_quote_segment(char *str, int *i,
	t_lexer_context *ctx, char **result)
{
	char	*value;
	char	*tmp;

	value = NULL;
	if (str[*i] == '\\')
		value = process_escaped_char(str, i);
	else if (str[*i] == '$' && str[*i + 1] && !is_whitespace(str[*i + 1])
		&& str[*i + 1] != '"')
		value = process_env_in_quotes(str, i, ctx);
	else
		value = process_literal_in_quotes(str, i);
	if (!value)
		return (0);
	tmp = ft_strjoin(*result, value);
	free(value);
	free(*result);
	if (!tmp)
		return (0);
	*result = tmp;
	return (1);
}

char	*extract_double_quoted(char *str, int *i, t_env *env, int *exit_status)
{
	char			*result;
	t_lexer_context	ctx;

	ctx.env = env;
	ctx.exit_status = exit_status;
	ctx.after_redirect = NULL;
	(*i)++;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (!process_double_quote_segment(str, i, &ctx, &result))
		{
			free(result);
			return (NULL);
		}
	}
	if (!str[*i])
	{
		free(result);
		return (NULL);
	}
	(*i)++;
	return (result);
}
