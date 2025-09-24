/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_context	init_parse_context(char **args)
{
	t_parse_context	ctx;
	static t_cmd	*head = NULL;
	static t_cmd	*current_cmd = NULL;
	static int		arg_index = 0;
	static int		exit_status = 0;

	head = NULL;
	current_cmd = NULL;
	arg_index = 0;
	exit_status = 0;
	ctx.head = &head;
	ctx.current_cmd = &current_cmd;
	ctx.args = args;
	ctx.arg_index = &arg_index;
	ctx.exit_status = &exit_status;
	return (ctx);
}

int	finalize_parsing(t_parse_context *ctx, char **args)
{
	if (*ctx->current_cmd)
	{
		if (!finalize_command(*ctx->current_cmd, args,
				*ctx->arg_index, ctx->exit_status))
		{
			free_cmd_args(args);
			cleanup_parse_error(NULL, *ctx->head, ctx->exit_status);
			return (0);
		}
		free(args);
	}
	else
	{
		free_cmd_args(args);
	}
	return (1);
}
