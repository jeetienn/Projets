/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	allocate_and_copy_args(t_cmd *cmd, char **args,
				int arg_index, int *exit_status)
{
	int	i;

	cmd->args = ft_calloc(arg_index + 1, sizeof(char *));
	if (!cmd->args)
	{
		display_error("malloc", NULL, "memory allocation failed", exit_status);
		return (0);
	}
	i = 0;
	while (i < arg_index)
	{
		cmd->args[i] = args[i];
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}

int	finalize_command(t_cmd *cmd, char **args, int arg_index, int *exit_status)
{
	if (arg_index == 0)
		return (1);
	if (!allocate_and_copy_args(cmd, args, arg_index, exit_status))
		return (0);
	if (arg_index > 0 && args[0])
	{
		cmd->cmd = ft_strdup(args[0]);
		if (!cmd->cmd)
		{
			free(cmd->args);
			display_error("malloc", NULL,
				"memory allocation failed", exit_status);
			return (0);
		}
	}
	return (1);
}

static int	process_token(t_token **current, t_parse_context *ctx)
{
	if ((*current)->type == TOKEN_PIPE)
		return (handle_pipe_token(ctx));
	if ((*current)->type == TOKEN_HEREDOC)
		return (handle_heredoc_token(current, ctx));
	if ((*current)->type == TOKEN_REDIRECT_IN)
		return (handle_redirect_in_token(current, ctx));
	if ((*current)->type == TOKEN_REDIRECT_OUT)
		return (handle_redirect_out_token(current, ctx, 0));
	if ((*current)->type == TOKEN_REDIRECT_APPEND)
		return (handle_redirect_out_token(current, ctx, 1));
	if ((*current)->type == TOKEN_WORD)
		return (handle_word_token(*current, ctx));
	return (0);
}

static int	process_all_tokens(t_token *tokens, t_parse_context *ctx)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!process_token(&current, ctx))
			return (0);
		current = current->next;
	}
	return (1);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_parse_context	ctx;
	char			**args;

	args = ft_calloc(100, sizeof(char *));
	if (!args)
	{
		free_tokens(tokens);
		return (NULL);
	}
	ctx = init_parse_context(args);
	if (!process_all_tokens(tokens, &ctx))
	{
		free_tokens(tokens);
		free_cmd_args(args);
		cleanup_parse_error(NULL, *ctx.head, ctx.exit_status);
		return (NULL);
	}
	if (!finalize_parsing(&ctx, args))
	{
		free_tokens(tokens);
		free_cmd_args(args);
		return (NULL);
	}
	free_tokens(tokens);
	return (*ctx.head);
}
