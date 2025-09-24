#include "so_long.h"

void	draw_render_map(t_data *data, int x, int y, char tile)
{
	if (tile == '1')
		mlx_put_image_to_window(data->mlx, data->window, data->img_wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == '0')
		mlx_put_image_to_window(data->mlx, data->window, data->img_floor,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'C')
		mlx_put_image_to_window(data->mlx, data->window, data->img_collectible,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(data->mlx, data->window, data->img_exit,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
		mlx_put_image_to_window(data->mlx, data->window, data->img_player,
			x * TILE_SIZE, y * TILE_SIZE);
	else
		clean_exit(data, "Wrong character in the map");
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			draw_render_map(data, x, y, data->map[y][x]);
			x++;
		}
		y++;
	}
}
