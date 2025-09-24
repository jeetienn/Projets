/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2025/06/10 17:29:07 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_and_exit_cmd(t_cmd *cmd, t_env *env, int exit_status)
{
	free_cmd(cmd);
	cleanup_shell(env, exit_status);
}

static int	handle_all_redirections(t_cmd *cmd,
		int *exit_status, int is_child, t_env *env)
{
	if (cmd->heredocs && !setup_heredoc_pipe(cmd, exit_status))
	{
		if (is_child)
			cleanup_and_exit_cmd(cmd, env, *exit_status);
		return (0);
	}
	if (!handle_input_redirect(cmd, exit_status))
	{
		if (is_child)
			cleanup_and_exit_cmd(cmd, env, *exit_status);
		return (0);
	}
	if (!handle_redirects_wrapper(cmd, exit_status))
	{
		if (is_child)
			cleanup_and_exit_cmd(cmd, env, *exit_status);
		return (0);
	}
	return (1);
}

void	execute_cmd(t_cmd *cmd, t_env *env, int *exit_status, int is_child)
{
	if (!cmd || !cmd->cmd)
	{
		*exit_status = 1;
		if (is_child)
			cleanup_and_exit_cmd(cmd, env, *exit_status);
		return ;
	}
	if (!handle_all_redirections(cmd, exit_status, is_child, env))
		return ;
	if (is_builtin(cmd->cmd))
		execute_builtin(cmd, &env, exit_status);
	else
		execute_command(cmd->args, env, exit_status);
	if (ft_strcmp(cmd->cmd, "export") && is_child)
		cleanup_and_exit_cmd(cmd, env, *exit_status);
}

static void	execute_single_command(t_cmd *pipeline,
		t_env *env, int *exit_status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		display_error("fork", NULL, "operation failed", exit_status);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_cmd(pipeline, env, exit_status, 1);
		exit(*exit_status);
	}
	else
	{
		wait_for_child(pid, exit_status);
	}
}

void	execute_pipeline(t_cmd *pipeline, t_env *env, int *exit_status)
{
	t_pipeline_init_context	ctx;

	if (!prepare_heredocs(pipeline, exit_status)
		|| handle_single_builtin(pipeline, env, exit_status))
		return ;
	if (!pipeline || count_pipeline_commands(pipeline) == 0)
		return (*exit_status = 0, (void)0);
	ctx.cmd_count = count_pipeline_commands(pipeline);
	if (ctx.cmd_count == 1)
		return (execute_single_command(pipeline, env, exit_status), (void)0);
	ctx.pids = ft_calloc(ctx.cmd_count, sizeof(pid_t));
	if (!ctx.pids)
		return (display_error("malloc", NULL, "memory allocation failed",
				exit_status), (void)0);
	ctx.pipeline = pipeline;
	ctx.env = env;
	ctx.exit_status = exit_status;
	setup_and_run_pipeline(&ctx);
}
