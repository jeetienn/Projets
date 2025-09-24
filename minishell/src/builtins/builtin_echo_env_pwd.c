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

static void	write_echo_args(t_cmd *cmd, int start_index)
{
	int	i;

	i = start_index;
	while (cmd->args[i])
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

static int	process_echo_options(t_cmd *cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		if (!check_echo_option(cmd->args[i]))
			break ;
		newline = 0;
		i++;
	}
	return (newline);
}

void	builtin_echo(t_cmd *cmd, t_env **env, int *exit_status)
{
	int	newline;
	int	i;

	(void)env;
	newline = process_echo_options(cmd);
	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		if (!check_echo_option(cmd->args[i]))
			break ;
		i++;
	}
	write_echo_args(cmd, i);
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	*exit_status = 0;
}

void	builtin_env(t_cmd *cmd, t_env **env, int *exit_status)
{
	t_env	*current;

	current = *env;
	if (cmd->args[1])
	{
		error_too_many_args("env", exit_status);
		return ;
	}
	while (current)
	{
		ft_putstr_fd(current->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current->value, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
	*exit_status = 0;
}

void	builtin_pwd(t_cmd *cmd, t_env **env, int *exit_status)
{
	char	*cwd;

	(void)cmd;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		free(cwd);
		*exit_status = 0;
	}
	else
	{
		display_error("pwd", NULL, "error getting current directory",
			exit_status);
	}
}
