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

int	handle_input_redirect(t_cmd *cmd, int *exit_status)
{
	int	fd_in;

	fd_in = -1;
	if (cmd->redirect_in)
	{
		fd_in = open(cmd->redirect_in, O_RDONLY);
		if (fd_in == -1)
		{
			error_no_such_file(NULL, cmd->redirect_in, exit_status);
			return (0);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	return (1);
}

static int	open_output_file(t_redirect *current)
{
	int	fd_out;

	if (current->append)
		fd_out = open(current->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(current->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd_out);
}

int	handle_output_redirects(t_cmd *cmd, int *exit_status)
{
	t_redirect	*current;
	int			fd_out;

	current = cmd->redirects_out;
	fd_out = -1;
	while (current)
	{
		fd_out = open_output_file(current);
		if (fd_out == -1)
		{
			error_permission_denied(NULL, current->filename, exit_status);
			return (0);
		}
		if (current->next)
			close(fd_out);
		current = current->next;
	}
	return (fd_out);
}

int	finalize_output_redirect(t_cmd *cmd, int *exit_status)
{
	t_redirect	*current;
	int			fd_out;

	current = cmd->redirects_out;
	fd_out = -1;
	while (current && current->next)
		current = current->next;
	if (current)
	{
		fd_out = open_output_file(current);
		if (fd_out == -1)
		{
			error_permission_denied(NULL, current->filename, exit_status);
			return (0);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (1);
}

int	handle_redirects_wrapper(t_cmd *cmd, int *exit_status)
{
	if (cmd->redirects_out && !handle_output_redirects(cmd, exit_status))
		return (0);
	if (cmd->redirects_out && !finalize_output_redirect(cmd, exit_status))
		return (0);
	return (1);
}
