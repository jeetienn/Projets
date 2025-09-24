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

void	error_no_such_file(const char *cmd, const char *file, int *exit_code)
{
	display_error(cmd, file, "No such file or directory", exit_code);
	if (exit_code)
		*exit_code = 1;
}

void	error_permission_denied(const char *cmd,
					const char *file, int *exit_code)
{
	display_error(cmd, file, "Permission denied", exit_code);
	if (exit_code)
		*exit_code = 1;
}

void	error_too_many_args(const char *cmd, int *exit_code)
{
	display_error(cmd, NULL, "too many arguments", exit_code);
	if (exit_code)
		*exit_code = 1;
}

void	error_numeric_required(const char *cmd, const char *arg, int *exit_code)
{
	display_error(cmd, arg, "numeric argument required", exit_code);
	if (exit_code)
		*exit_code = 2;
}

void	error_home_not_set(int *exit_code)
{
	display_error("cd", NULL, "HOME not set", exit_code);
	if (exit_code)
		*exit_code = 1;
}
