/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *envp_line)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(envp_line, '=');
	if (!equal)
		return (free(node), NULL);
	node->key = ft_strndup(envp_line, equal - envp_line);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(equal + 1);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	node->next = NULL;
	return (node);
}

static char	*setup_pwd_env(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strjoin("PWD=", cwd));
	else
		return (ft_strdup("PWD=/unknown"));
}

static t_env	*build_env_list(char **default_env)
{
	t_env	*env;
	t_env	*node;
	int		i;

	env = NULL;
	i = 0;
	while (default_env[i])
	{
		node = create_env_node(default_env[i]);
		if (!node)
		{
			if (i == 0)
				free(default_env[0]);
			free_env(env);
			return (NULL);
		}
		node->next = env;
		env = node;
		i++;
	}
	return (env);
}

t_env	*init_empty_env(void)
{
	t_env	*env;
	char	*default_env[4];

	default_env[0] = setup_pwd_env();
	default_env[1] = "SHLVL=1";
	default_env[2] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	default_env[3] = NULL;
	if (!default_env[0])
		return (NULL);
	env = build_env_list(default_env);
	if (default_env[0])
		free(default_env[0]);
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	if (!envp || !envp[0])
		return (init_empty_env());
	env = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
		{
			free_env(env);
			return (NULL);
		}
		node->next = env;
		env = node;
		i++;
	}
	return (env);
}
