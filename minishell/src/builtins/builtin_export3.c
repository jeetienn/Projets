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

void	builtin_export(t_cmd *cmd, t_env **env, int *exit_status)
{
	int					error_occurred;
	int					arg_index;
	t_export_context	ctx;

	if (!cmd->args[1])
	{
		export_no_args(cmd, env, exit_status);
		return ;
	}
	error_occurred = 0;
	arg_index = 1;
	ctx = (t_export_context){env, &arg_index,
		&error_occurred, exit_status};
	while (cmd->args[arg_index])
		process_export_arg(cmd, &ctx);
	if (error_occurred)
		*exit_status = 1;
	else
		*exit_status = 0;
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		i;
	int		j;
	char	*result_info[2];

	if (!str)
		return (NULL);
	result = malloc(strlen(str) * 4 + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	result_info[0] = result;
	result_info[1] = (char *)&j;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			process_variable(str, &i, env, result_info);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	handle_export_with_equals(char *key,
	char *eq, t_export_context *ctx)
{
	char	*raw_value;
	char	*expanded_value;

	raw_value = ft_strdup(eq + 1);
	if (!raw_value)
	{
		free(key);
		display_error("export", NULL,
			"memory allocation failed", ctx->exit_status);
		return (1);
	}
	expanded_value = expand_variables(raw_value, *ctx->env);
	free(raw_value);
	if (!expanded_value)
	{
		free(key);
		display_error("export", NULL,
			"memory allocation failed", ctx->exit_status);
		return (1);
	}
	update_env(ctx->env, key, expanded_value, ctx->exit_status);
	(*ctx->arg_index)++;
	return (0);
}

static void	handle_invalid_export_key(char *key, t_export_context *ctx)
{
	handle_invalid_key(key, ctx->error_occurred);
	free(key);
	(*ctx->arg_index)++;
}

void	process_export_arg(t_cmd *cmd, t_export_context *ctx)
{
	char	*arg;
	char	*eq;
	char	*key;

	arg = cmd->args[*ctx->arg_index];
	eq = ft_strchr(arg, '=');
	key = extract_key(arg, eq);
	if (!key)
	{
		display_error("export", NULL,
			"memory allocation failed", ctx->exit_status);
		return ;
	}
	if (!is_valid_identifier(key))
	{
		handle_invalid_export_key(key, ctx);
		return ;
	}
	if (!eq)
		handle_export_without_equals(key, ctx->arg_index);
	else
		handle_export_with_equals(key, eq, ctx);
}
