/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:54:14 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 16:55:40 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	clean_graphics(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_player)
		mlx_destroy_image(data->mlx, data->img_player);
	if (data->img_floor)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
}

static void	free_map(t_data *data)
{
	int	i;

	if (!data || !data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

int	is_valid_map_file(char *filename)
{
	size_t	len;

	len = 0;
	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strcmp(filename + (len - 4), ".ber") == 0)
		return (1);
	return (0);
}

int	clean_exit(t_data *data, char *error_msg)
{
	if (error_msg)
		write(2, error_msg, ft_strlen(error_msg));
	clean_graphics(data);
	free_map(data);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
	exit(0);
}
