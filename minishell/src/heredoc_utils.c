/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:00:00 by jeetienn          #+#    #+#             */
/*   Updated: 2024/12/04 12:00:00 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal = 2;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	*setup_heredoc_signals(void (*handler)(int))
{
	void	(*old_handler)(int);

	old_handler = signal(SIGINT, handler);
	return (old_handler);
}

char	*append_heredoc_line(char *content, char *line, int *exit_status)
{
	char	*temp;

	temp = content;
	content = ft_strjoin(content, line);
	free(temp);
	if (!content)
	{
		display_error("heredoc", NULL, "memory allocation failed", exit_status);
		return (NULL);
	}
	temp = content;
	content = ft_strjoin(content, "\n");
	free(temp);
	if (!content)
	{
		display_error("heredoc", NULL, "memory allocation failed", exit_status);
		return (NULL);
	}
	return (content);
}

char	*handle_heredoc_end(char *content, char *line,
				void (*old_handler)(int), int *exit_status)
{
	if (!line)
	{
		if (g_signal == 2)
		{
			free(content);
			*exit_status = 130;
			signal(SIGINT, old_handler);
			return (NULL);
		}
		return (content);
	}
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return (content);
	}
	free(line);
	return (content);
}

int	process_single_heredoc(t_heredoc *heredoc, int *exit_status)
{
	heredoc->content = read_heredoc(heredoc->delim, exit_status);
	if (!heredoc->content && g_signal == 2)
	{
		g_signal = 0;
		return (0);
	}
	return (1);
}
