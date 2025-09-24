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

void	init_pipeline_data(t_pipeline_data *data, t_pipeline_init_context *ctx)
{
	data->stdin_copy = dup(STDIN_FILENO);
	data->stdout_copy = dup(STDOUT_FILENO);
	data->current = ctx->pipeline;
	data->prev_fd = -1;
	data->i = 0;
	data->env = ctx->env;
	data->pids = ctx->pids;
	data->exit_status = ctx->exit_status;
}

void	update_pipeline_state(t_pipeline_data *data)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (data->current->next)
	{
		close(data->pipe_fd[1]);
		data->prev_fd = data->pipe_fd[0];
	}
	data->current = data->current->next;
	data->i++;
}

// void	close_extra_fds(void)
// {
// 	int	fd;

// 	fd = 3;
// 	while (fd < 1024)
// 	{
// 		close(fd);
// 		fd++;
// 	}
// }
