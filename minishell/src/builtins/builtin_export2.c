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

void	update_env(t_env **env, char *key,
	char *value, int *exit_status)
{
	t_env					*current;
	t_env					*prev;
	t_env_creation_context	ctx;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_env_var(current, key, value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	ctx = (t_env_creation_context){key, value, exit_status};
	add_new_env_var(env, prev, &ctx);
}

int	handle_export_without_equals(char *key, int *arg_index)
{
	free(key);
	(*arg_index)++;
	return (0);
}

char	*get_env_var_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*extract_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	strncpy(var_name, str + start, len);
	var_name[len] = '\0';
	return (var_name);
}

void	process_variable(char *str, int *i, t_env *env, char **result_info)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	int		*j;

	result = result_info[0];
	j = (int *)result_info[1];
	(*i)++;
	var_name = extract_var_name(str, i);
	var_value = get_env_var_value(env, var_name);
	if (var_value)
	{
		strcpy(result + *j, var_value);
		*j += strlen(var_value);
	}
	free(var_name);
}
