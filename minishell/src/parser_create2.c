/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_heredocs(t_cmd *cmd)
{
	t_heredoc	*heredoc;
	t_heredoc	*next_heredoc;

	heredoc = cmd->heredocs;
	while (heredoc)
	{
		next_heredoc = heredoc->next;
		if (heredoc->delim)
			free(heredoc->delim);
		if (heredoc->content)
			free(heredoc->content);
		free(heredoc);
		heredoc = next_heredoc;
	}
}

void	free_cmd_single(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	free_cmd_args(cmd->args);
	if (cmd->redirect_in)
		free(cmd->redirect_in);
	free_cmd_redirects(cmd);
	free_cmd_heredocs(cmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_cmd_single(current);
		free(current);
		current = next;
	}
}
