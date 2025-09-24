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

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_env **env, int *exit_status)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		builtin_echo(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		builtin_env(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		builtin_export(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		builtin_unset(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		builtin_pwd(cmd, env, exit_status);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin_cd(cmd, env, exit_status);
}
