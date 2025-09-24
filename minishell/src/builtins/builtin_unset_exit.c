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

static void	remove_env_node(t_env **env, t_env *current, t_env *prev)
{
	if (prev)
		prev->next = current->next;
	else
		*env = current->next;
	free_env_node(current);
}

void	builtin_unset(t_cmd *cmd, t_env **env, int *exit_status)
{
	char	*key;
	t_env	*current;
	t_env	*prev;

	key = cmd->args[1];
	if (!key)
	{
		*exit_status = 0;
		return ;
	}
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			remove_env_node(env, current, prev);
			*exit_status = 0;
			return ;
		}
		prev = current;
		current = current->next;
	}
	*exit_status = 0;
}

static int	is_valid_long_long(char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

static void	handle_exit_args(t_cmd *cmd, int *exit_status, int *exit_code)
{
	if (cmd->args[1])
	{
		if (!is_valid_long_long(cmd->args[1]))
		{
			error_numeric_required("exit", cmd->args[1], exit_status);
			*exit_code = 2;
			return ;
		}
		if (cmd->args[2])
		{
			error_too_many_args("exit", exit_status);
			*exit_code = -1;
			return ;
		}
		*exit_code = ft_atoi(cmd->args[1]) & 255;
	}
}

void	builtin_exit(t_cmd *cmd, t_env **env, int *exit_status)
{
	int	exit_code;

	exit_code = *exit_status;
	ft_putstr_fd("exit\n", 2);
	handle_exit_args(cmd, exit_status, &exit_code);
	if (exit_code == -1)
		return ;
	free_cmd(cmd);
	cleanup_shell(*env, exit_code);
	exit(exit_code);
}
