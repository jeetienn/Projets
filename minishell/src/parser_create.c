/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirect_in = NULL;
	cmd->redirects_out = NULL;
	cmd->heredocs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_heredoc	*create_heredoc(char *delim)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delim = ft_strdup(delim);
	if (!heredoc->delim)
	{
		free(heredoc);
		return (NULL);
	}
	heredoc->content = NULL;
	heredoc->next = NULL;
	return (heredoc);
}

t_redirect	*create_redirect(char *filename, int append)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->filename = ft_strdup(filename);
	if (!redirect->filename)
	{
		free(redirect);
		return (NULL);
	}
	redirect->append = append;
	redirect->next = NULL;
	return (redirect);
}

void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd_redirects(t_cmd *cmd)
{
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	redirect = cmd->redirects_out;
	while (redirect)
	{
		next_redirect = redirect->next;
		if (redirect->filename)
			free(redirect->filename);
		free(redirect);
		redirect = next_redirect;
	}
}
