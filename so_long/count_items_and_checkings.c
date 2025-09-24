/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:52:15 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 16:53:48 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_items(t_data *data, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	is_rectangle(t_data *data)
{
	int	i;
	int	prev_len;

	i = 1;
	prev_len = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		if (prev_len != (int)ft_strlen(data->map[i]))
		{
			ft_printf("Error: The map is not rectangular .\n");
			return (0);
		}
		prev_len = ft_strlen(data->map[i]);
		i++;
	}
	return (1);
}

int	is_walled(t_data *data)
{
	int		i;
	int		height;

	i = 0;
	height = data->map_height;
	while (data->map[0][i] && data->map[data->map_height - 1][i])
	{
		if (data->map[0][i] != '1' || data->map[data->map_height - 1][i] != '1')
		{
			ft_printf("A wall is missing at top/bottom.\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (data->map[i][0] != '1'
			|| data->map[i][ft_strlen(data->map[i]) - 1] != '1')
			return (ft_printf("A wall is missing at left/right\n"), 0);
		i++;
	}
	return (1);
}

void	free_map_fill(char **map, int status)
{
	int	i;

	if (map)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
	if (status == 0)
		exit(0);
}
