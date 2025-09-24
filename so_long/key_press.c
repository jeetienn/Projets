/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:56:05 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 16:59:10 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player_pos(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map[y])
	{
		if (data->map[y][x] == 'P')
		{
			data->player_x = x * TILE_SIZE;
			data->player_y = y * TILE_SIZE;
			break ;
		}
		x++;
		if (data->map[y][x] == '\0')
		{
			x = 0;
			y++;
		}
	}
	data->pos_x = data->player_x / TILE_SIZE;
	data->pos_y = data->player_y / TILE_SIZE;
}

static int	check_movement(int keycode, t_data *data, int old_x, int old_y)
{
	int	new_x;
	int	new_y;

	new_x = old_x;
	new_y = old_y;
	if (keycode == 119 || keycode == 65362)
		new_y--;
	if (keycode == 115 || keycode == 65364)
		new_y++;
	if (keycode == 97 || keycode == 65361)
		new_x--;
	if (keycode == 100 || keycode == 65363)
		new_x++;
	if (new_x < 0 || new_x >= data->map_width || new_y < 0
		|| new_y >= data->map_height)
		return (0);
	if (data->map[new_y][new_x] == '1' ||
			(data->map[new_y][new_x] == 'E' && data->collectible_nb != 0))
		return (0);
	return ((new_y - old_y) + (new_x - old_x) * 2);
}

static void	update_player_position(int movement, int *new_x, int *new_y)
{
	if (movement == -1)
		*new_y -= 1;
	else if (movement == 1)
		*new_y += 1;
	else if (movement == -2)
		*new_x -= 1;
	else if (movement == 2)
		*new_x += 1;
}

void	handle_movement(int keycode, t_data *data, int *new_x, int *new_y)
{
	int	old_x;
	int	old_y;
	int	movement;

	old_x = data->player_x / TILE_SIZE;
	old_y = data->player_y / TILE_SIZE;
	*new_x = old_x;
	*new_y = old_y;
	movement = check_movement(keycode, data, old_x, old_y);
	update_player_position(movement, new_x, new_y);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window (data);
	handle_movement (keycode, data, &data->pos_x, &data->pos_y);
	update_map (data, data->pos_x, data->pos_y);
	draw_map (data);
	mlx_put_image_to_window (data->mlx, data->window, data->img_player,
		data->player_x, data->player_y);
	return (0);
}
