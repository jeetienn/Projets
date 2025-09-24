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

void	export_no_args(t_cmd *cmd, t_env **env, int *exit_status)
{
	builtin_env(cmd, env, exit_status);
}

void	handle_invalid_key(char *key, int *error_occurred)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*error_occurred = 1;
}

t_env	*create_new_env_node(t_env_creation_context *ctx)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(ctx->key);
		free(ctx->value);
		display_error("export", NULL,
			"memory allocation failed", ctx->exit_status);
		return (NULL);
	}
	new->key = ctx->key;
	new->value = ctx->value;
	new->next = NULL;
	return (new);
}

void	update_existing_env_var(t_env *current, char *key, char *value)
{
	free(current->value);
	current->value = value;
	free(key);
}

void	add_new_env_var(t_env **env, t_env *prev,
			t_env_creation_context *ctx)
{
	t_env	*new;

	new = create_new_env_node(ctx);
	if (new)
	{
		if (!*env)
			*env = new;
		else
			prev->next = new;
	}
}
