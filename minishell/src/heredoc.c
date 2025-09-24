/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/12/04 12:00:00 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc(char *delim, int *exit_status)
{
	char	*content;
	char	*line;
	void	(*old_handler)(int);

	content = ft_strdup("");
	old_handler = setup_heredoc_signals(heredoc_sigint_handler);
	if (!content)
	{
		signal(SIGINT, old_handler);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
			return (handle_heredoc_end(content, line, old_handler,
					exit_status));
		content = append_heredoc_line(content, line, exit_status);
		free(line);
		if (!content)
		{
			signal(SIGINT, old_handler);
			return (NULL);
		}
	}
}

int	prepare_heredocs(t_cmd *cmd, int *exit_status)
{
	t_cmd		*current_cmd;
	t_heredoc	*current_heredoc;

	current_cmd = cmd;
	while (current_cmd)
	{
		current_heredoc = current_cmd->heredocs;
		while (current_heredoc)
		{
			if (!process_single_heredoc(current_heredoc, exit_status))
				return (0);
			current_heredoc = current_heredoc->next;
		}
		current_cmd = current_cmd->next;
	}
	return (1);
}

static int	write_heredoc_content(t_heredoc *current, int pipefd)
{
	t_heredoc	*last;

	last = current;
	while (last && last->next)
		last = last->next;
	if (last && last->content)
		write(pipefd, last->content, ft_strlen(last->content));
	return (1);
}

static int	create_heredoc_pipe(int *pipefd, int *exit_status)
{
	if (pipe(pipefd) == -1)
	{
		display_error("heredoc", NULL, "pipe creation failed", exit_status);
		return (0);
	}
	return (1);
}

int	setup_heredoc_pipe(t_cmd *cmd, int *exit_status)
{
	t_heredoc	*current;
	int			pipefd[2];

	if (!cmd->heredocs)
		return (1);
	if (!create_heredoc_pipe(pipefd, exit_status))
		return (0);
	current = cmd->heredocs;
	write_heredoc_content(current, pipefd[1]);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (1);
}
