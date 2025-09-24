/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_path_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (path && access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	t_env	*node;
	char	**dirs;
	char	*path;
	int		i;

	path = NULL;
	node = find_path_node(env);
	if (!node)
		return (NULL);
	dirs = ft_split(node->value, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		path = test_path_dir(dirs[i], cmd);
		if (path)
			break ;
		i++;
	}
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (path);
}

int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	free_array_partial(char **array, int index)
{
	while (index > 0)
		free(array[--index]);
	free(array);
}

char	**env_to_array(t_env *env)
{
	int		count;
	char	**array;
	int		i;
	t_env	*current;
	char	*tmp;

	count = count_env_nodes(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		if (!tmp)
			return (free_array_partial(array, i), NULL);
		array[i] = ft_strjoin(tmp, current->value);
		if (free(tmp), !array[i])
			return (free_array_partial(array, i), NULL);
		current = current->next;
		i++;
	}
	return (array[i] = NULL, array);
}
