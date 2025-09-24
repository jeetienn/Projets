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

static void	setup_child_fds(int prev_fd, int *pipe_fd, t_cmd *current)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close_extra_fds();
}

static int	create_pipeline_process(t_pipeline_data *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		display_error("fork", NULL, "operation failed", data->exit_status);
		if (data->current->next)
		{
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
		}
		return (0);
	}
	if (data->pids[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_fds(data->prev_fd, data->pipe_fd, data->current);
		execute_cmd(data->current, data->env, data->exit_status, 1);
		free(data->pids);
		free_cmd(data->current);
		cleanup_shell(data->env, *data->exit_status);
	}
	return (1);
}

static void	wait_all_processes(pid_t *pids, int cmd_count, int *exit_status)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				*exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
			}
		}
		i++;
	}
}

static void	cleanup_pipeline(t_pipeline_data *data, int cmd_count)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	dup2(data->stdin_copy, STDIN_FILENO);
	dup2(data->stdout_copy, STDOUT_FILENO);
	close(data->stdin_copy);
	close(data->stdout_copy);
	wait_all_processes(data->pids, cmd_count, data->exit_status);
	free(data->pids);
}

int	setup_and_run_pipeline(t_pipeline_init_context *ctx)
{
	t_pipeline_data	data;

	init_pipeline_data(&data, ctx);
	while (data.current)
	{
		if (data.current->next && pipe(data.pipe_fd) == -1)
		{
			display_error("pipe", NULL, "operation failed", data.exit_status);
			cleanup_pipeline(&data, data.i);
			return (0);
		}
		if (!create_pipeline_process(&data, data.i))
		{
			cleanup_pipeline(&data, data.i);
			return (0);
		}
		update_pipeline_state(&data);
	}
	cleanup_pipeline(&data, ctx->cmd_count);
	return (1);
}
