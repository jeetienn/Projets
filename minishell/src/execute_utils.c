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

void	wait_for_child(pid_t pid, int *exit_status)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	cleanup_and_exit(t_cleanup_data *data)
{
	int	i;

	display_system_error(data->args[0], NULL, data->exit_status);
	free(data->path);
	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	free_cmd_args(data->args);
	cleanup_shell(data->env, 126);
}

int	count_pipeline_commands(t_cmd *pipeline)
{
	int		cmd_count;
	t_cmd	*current;

	cmd_count = 0;
	current = pipeline;
	while (current)
	{
		cmd_count++;
		current = current->next;
	}
	return (cmd_count);
}

int	handle_single_builtin(t_cmd *pipeline, t_env *env, int *exit_status)
{
	if (!pipeline || pipeline->next)
		return (0);
	if (!is_builtin(pipeline->cmd))
		return (0);
	if (ft_strcmp(pipeline->cmd, "cd") == 0)
	{
		execute_cmd(pipeline, env, exit_status, 0);
		return (1);
	}
	if (ft_strcmp(pipeline->cmd, "export") == 0)
	{
		execute_cmd(pipeline, env, exit_status, 0);
		return (1);
	}
	if (ft_strcmp(pipeline->cmd, "unset") == 0)
	{
		execute_cmd(pipeline, env, exit_status, 0);
		return (1);
	}
	if (ft_strcmp(pipeline->cmd, "exit") == 0)
	{
		execute_cmd(pipeline, env, exit_status, 0);
		return (1);
	}
	return (0);
}
