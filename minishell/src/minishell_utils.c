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

int	g_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static char	*create_tilde_path(char *cwd, char *relative_path)
{
	char	*path;

	if (*relative_path == '\0')
	{
		free(cwd);
		return (ft_strdup("~"));
	}
	path = ft_strjoin("~", relative_path);
	free(cwd);
	return (path);
}

static char	*build_display_path(char *cwd, char *home)
{
	char	*relative_path;

	if (!cwd)
		return (ft_strdup("?"));
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		relative_path = cwd + ft_strlen(home);
		return (create_tilde_path(cwd, relative_path));
	}
	return (cwd);
}

char	*format_prompt(t_env *env)
{
	char	*cwd;
	char	*home;
	char	*display_path;
	char	*prompt;
	char	*final_prompt;

	cwd = getcwd(NULL, 0);
	home = get_env_value(env, "HOME");
	display_path = build_display_path(cwd, home);
	prompt = ft_strjoin("minishell:", display_path);
	if (!prompt)
	{
		free(display_path);
		return (ft_strdup("minishell:?"));
	}
	final_prompt = ft_strjoin(prompt, "$ ");
	free(prompt);
	free(display_path);
	if (!final_prompt)
		return (ft_strdup("minishell:?"));
	return (final_prompt);
}
