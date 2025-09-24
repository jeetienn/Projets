/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redirect_to_list(t_cmd *cmd, t_redirect *redirect)
{
	t_redirect	*tmp;

	if (!cmd->redirects_out)
		cmd->redirects_out = redirect;
	else
	{
		tmp = cmd->redirects_out;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redirect;
	}
}

static char	*get_redirect_symbol(int append)
{
	if (append)
		return (">>");
	return (">");
}

void	cleanup_parse_error(char **args, t_cmd *head, int *exit_status)
{
	free(args);
	free_cmd(head);
	*exit_status = 1;
}

int	handle_redirect_out_token(t_token **current, t_parse_context *ctx,
	int append)
{
	t_redirect	*redirect;

	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
	{
		display_error("syntax", get_redirect_symbol(append),
			"expected filename", ctx->exit_status);
		return (0);
	}
	if (!init_cmd_if_needed(ctx->head, ctx->current_cmd))
		return (0);
	redirect = create_redirect((*current)->value, append);
	if (!redirect)
		return (0);
	add_redirect_to_list(*ctx->current_cmd, redirect);
	return (1);
}

int	handle_word_token(t_token *current, t_parse_context *ctx)
{
	if (!init_cmd_if_needed(ctx->head, ctx->current_cmd))
		return (0);
	if (*ctx->arg_index >= 99)
		return (0);
	ctx->args[*ctx->arg_index] = ft_strdup(current->value);
	if (!ctx->args[*ctx->arg_index])
	{
		display_error("malloc", NULL, "memory allocation failed",
			ctx->exit_status);
		return (0);
	}
	(*ctx->arg_index)++;
	return (1);
}
