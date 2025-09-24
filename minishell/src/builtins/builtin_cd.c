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

static t_env	*create_new_pwd_node(char *cwd, int *exit_status)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(cwd);
		display_error("malloc", NULL, "memory allocation failed", exit_status);
		return (NULL);
	}
	new->key = ft_strdup("PWD");
	new->value = cwd;
	new->next = NULL;
	return (new);
}

static void	update_existing_pwd(t_env **env, char *cwd, int *exit_status)
{
	t_env	*current;
	t_env	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = cwd;
			return ;
		}
		current = current->next;
	}
	new = create_new_pwd_node(cwd, exit_status);
	if (new)
	{
		new->next = *env;
		*env = new;
	}
}

static void	update_pwd(t_env **env, int *exit_status)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		display_error("cd", NULL, "error getting current directory",
			exit_status);
		return ;
	}
	update_existing_pwd(env, cwd, exit_status);
}

static char	*get_cd_path(t_cmd *cmd, t_env *env)
{
	if (cmd->args[1])
		return (cmd->args[1]);
	return (get_env_value(env, "HOME"));
}

void	builtin_cd(t_cmd *cmd, t_env **env, int *exit_status)
{
	char	*path;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		*exit_status = 1;
		return ;
	}
	path = get_cd_path(cmd, *env);
	if (!path)
	{
		error_home_not_set(exit_status);
		return ;
	}
	if (chdir(path) == -1)
	{
		error_no_such_file("cd", path, exit_status);
	}
	else
	{
		update_pwd(env, exit_status);
		if (*exit_status == 0)
			*exit_status = 0;
	}
}
