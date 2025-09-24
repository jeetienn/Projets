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

void	display_error(const char *cmd, const char *arg,
				const char *message, int *exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
	if (exit_code)
		*exit_code = 1;
}

void	display_system_error(const char *cmd, const char *arg, int *exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd((char *)strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (exit_code)
		*exit_code = 1;
}

void	error_command_not_found(const char *cmd, int *exit_code)
{
	display_error(NULL, cmd, "command not found", exit_code);
	if (exit_code)
		*exit_code = 127;
}
