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

static char	*resolve_command_path(char **args, t_env *env, int *exit_status)
{
	char	*path;

	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
		else
		{
			error_no_such_file(NULL, args[0], exit_status);
			return (NULL);
		}
	}
	else if (args[0][0] == '.' && args[0][1] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
		else
		{
			error_no_such_file(NULL, args[0], exit_status);
			return (NULL);
		}
	}
	else
		path = get_path_from_env(args[0], env, exit_status);
	return (path);
}

char	*get_path_from_env(char *cmd, t_env *env, int *exit_status)
{
	char	*path;

	path = get_path(cmd, env);
	if (!path)
	{
		error_command_not_found(cmd, exit_status);
		return (NULL);
	}
	return (path);
}

void	close_extra_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

static void	execute_child_process(char *path, char **args,
				t_env *env, int *exit_status)
{
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_extra_fds();
	envp = env_to_array(env);
	if (!envp)
	{
		display_error("env", NULL, "allocation failed", exit_status);
		free(path);
		free_cmd_args(args);
		cleanup_shell(env, 1);
	}
	execve(path, args, envp);
	cleanup_and_exit(&(t_cleanup_data){path, envp, args, env, exit_status});
}

void	execute_command(char **args, t_env *env, int *exit_status)
{
	char	*path;
	pid_t	pid;

	if (!args || !args[0])
	{
		*exit_status = 1;
		return ;
	}
	path = resolve_command_path(args, env, exit_status);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
	{
		display_error("fork", NULL, "failed", exit_status);
		free(path);
		return ;
	}
	if (pid == 0)
		execute_child_process(path, args, env, exit_status);
	wait_for_child(pid, exit_status);
	free(path);
}
