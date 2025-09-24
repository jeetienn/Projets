/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:50:39 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:52:07 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_tile_image(t_data *data, int x, int y)
{
	char	tile;
	int		px;
	int		py;

	tile = data->map[y][x];
	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	mlx_put_image_to_window(data->mlx, data->window,
		data->img_floor, px, py);
	if (tile == '1')
		mlx_put_image_to_window(data->mlx, data->window,
			data->img_wall, px, py);
	else if (tile == 'C')
		mlx_put_image_to_window(data->mlx, data->window,
			data->img_collectible, px, py);
	else if (tile == 'E')
		mlx_put_image_to_window(data->mlx, data->window,
			data->img_exit, px, py);
	else if (tile == 'P')
		mlx_put_image_to_window(data->mlx, data->window,
			data->img_player, px, py);
}

void	check_collectibles_and_exit(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == 'C')
	{
		data->collectible_nb--;
		data->map[new_y][new_x] = '0';
	}
	if (data->map[new_y][new_x] == 'E' && data->collectible_nb == 0)
	{
		clean_exit(data, "You win!\n");
	}
}

void	update_map(t_data *data, int new_x, int new_y)
{
	int		old_x;
	int		old_y;

	old_x = data->player_x / TILE_SIZE;
	old_y = data->player_y / TILE_SIZE;
	if (new_x == old_x && new_y == old_y)
		return ;
	data->move++;
	ft_printf("Moves : %d\n", data->move);
	ft_printf("to collect : %d\n", data->collectible_nb);
	check_collectibles_and_exit(data, new_x, new_y);
	data->map[old_y][old_x] = '0';
	put_tile_image(data, old_x, old_y);
	data->last_tile = data->map[new_y][new_x];
	data->map[new_y][new_x] = 'P';
	put_tile_image(data, new_x, new_y);
	data->player_x = new_x * TILE_SIZE;
	data->player_y = new_y * TILE_SIZE;
}
