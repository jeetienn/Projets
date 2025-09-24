/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd_if_needed(t_cmd **head, t_cmd **current_cmd)
{
	if (!*current_cmd)
	{
		*current_cmd = create_cmd();
		if (!*current_cmd)
			return (NULL);
		if (!*head)
			*head = *current_cmd;
	}
	return (*current_cmd);
}

int	handle_pipe_token(t_parse_context *ctx)
{
	t_cmd	*next_cmd;

	if (!*ctx->current_cmd || (*ctx->arg_index == 0
			&& !(*ctx->current_cmd)->heredocs))
	{
		display_error("syntax", "|", "unexpected token", ctx->exit_status);
		return (0);
	}
	if (!init_cmd_if_needed(ctx->head, ctx->current_cmd))
		return (0);
	if (*ctx->arg_index > 0)
	{
		if (!finalize_command(*ctx->current_cmd, ctx->args,
				*ctx->arg_index, ctx->exit_status))
			return (0);
	}
	next_cmd = create_cmd();
	if (!next_cmd)
		return (0);
	(*ctx->current_cmd)->next = next_cmd;
	*ctx->current_cmd = next_cmd;
	*ctx->arg_index = 0;
	ft_memset(ctx->args, 0, 100 * sizeof(char *));
	return (1);
}

int	handle_heredoc_token(t_token **current, t_parse_context *ctx)
{
	t_heredoc	*heredoc;
	t_heredoc	*tmp;

	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
	{
		display_error("syntax", "<<", "expected delimiter", ctx->exit_status);
		return (0);
	}
	if (!init_cmd_if_needed(ctx->head, ctx->current_cmd))
		return (0);
	heredoc = create_heredoc((*current)->value);
	if (!heredoc)
		return (0);
	if (!(*ctx->current_cmd)->heredocs)
		(*ctx->current_cmd)->heredocs = heredoc;
	else
	{
		tmp = (*ctx->current_cmd)->heredocs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = heredoc;
	}
	return (1);
}

int	handle_redirect_in_token(t_token **current, t_parse_context *ctx)
{
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
	{
		display_error("syntax", "<", "expected filename", ctx->exit_status);
		return (0);
	}
	if (!init_cmd_if_needed(ctx->head, ctx->current_cmd))
		return (0);
	(*ctx->current_cmd)->redirect_in = ft_strdup((*current)->value);
	if (!(*ctx->current_cmd)->redirect_in)
		return (0);
	return (1);
}
