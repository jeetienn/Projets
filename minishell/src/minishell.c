/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2025/06/10 16:58:56 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_input(char *line, t_env *env, int *exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line[0])
		return (1);
	add_history(line);
	tokens = lexer(line, env, exit_status);
	if (!tokens)
	{
		*exit_status = 1;
		return (1);
	}
	cmd = parse_tokens(tokens);
	if (!cmd)
		return (1);
	signal(SIGINT, SIG_IGN);
	execute_pipeline(cmd, env, exit_status);
	signal(SIGINT, sigint_handler);
	free_cmd(cmd);
	return (g_signal != -1);
}

static int	prompt_loop(t_env *env, int *exit_status)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = format_prompt(env);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			return (0);
		}
		if (!execute_input(line, env, exit_status))
		{
			free(line);
			return (0);
		}
		free(line);
		g_signal = 0;
	}
	return (1);
}

static t_env	*init_shell(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (env);
}

void	cleanup_shell(t_env *env, int exit_status)
{
	(void)exit_status;
	if (env)
		free_env(env);
	clear_history();
	exit(exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	t_env	*env;

	exit_status = 0;
	env = init_shell(argc, argv, envp);
	if (!env)
	{
		display_error("init", NULL, "environment allocation failed",
			&exit_status);
		cleanup_shell(NULL, exit_status);
		return (exit_status);
	}
	if (!prompt_loop(env, &exit_status))
		cleanup_shell(env, exit_status);
	cleanup_shell(env, exit_status);
	return (exit_status);
}
