/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:23:40 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:41:44 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_data *data)
{
	int	i;

	i = 0;
	mlx_destroy_image(data->mlx, data->img_wall);
	mlx_destroy_image(data->mlx, data->img_floor);
	mlx_destroy_image(data->mlx, data->img_player);
	mlx_destroy_image(data->mlx, data->img_exit);
	mlx_destroy_image(data->mlx, data->img_collectible);
	mlx_destroy_window(data->mlx, data->window);
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}

// void	draw_map(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	if (!data->mlx || !data->window)
// 	{
// 		ft_putstr_fd("Error: MLX or window not initialized\n", 2);
// 		return ;
// 	}
// 	while (y < data->map_height)
// 	{
// 		x = 0;
// 		while (x < data->map_width)
// 		{
// 			if (data->map[y][x] == '1' && data->img_wall)
// 				mlx_put_image_to_window(data->mlx, data->window,
// 					data->img_wall, x * TILE_SIZE, y * TILE_SIZE);
// 			else if (data->map[y][x] == '0' && data->img_floor)
// 				mlx_put_image_to_window(data->mlx, data->window,
// 					data->img_floor, x * TILE_SIZE, y * TILE_SIZE);
// 			else if (data->map[y][x] == 'P' && data->img_player)
// 				mlx_put_image_to_window(data->mlx, data->window,
// 					data->img_player, x * TILE_SIZE, y * TILE_SIZE);
// 			else if (data->map[y][x] == 'E' && data->img_exit)
// 				mlx_put_image_to_window(data->mlx, data->window,
// 					data->img_exit, x * TILE_SIZE, y * TILE_SIZE);
// 			else if (data->map[y][x] == 'C' && data->img_collectible)
// 				mlx_put_image_to_window(data->mlx, data->window,
// 					data->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int	init_data(t_data *data, char *map_file)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (write(2, "Erreur : mlx_init failed\n", 25), 1);
	}
	if (load_map(data, map_file) < 0)
		return (clean_exit(data, "Error loading map\n"));
	data->window = mlx_new_window(data->mlx, data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE, "So_Long");
	init_player_pos(data);
	if (!data->window)
	{
		close_window(data);
		return (write(2, "Erreur : window failed\n", 24), 1);
	}
	if (!is_true_map(data))
		return (clean_exit(data, "Invalid map configuration\n"), 1);
	return (0);
}

int	load_tiles(t_data *data)
{
	int	img_width;
	int	img_height;

	data->img_wall = mlx_xpm_file_to_image(data->mlx,
			"./tiles/wall.xpm", &img_width, &img_height);
	data->img_floor = mlx_xpm_file_to_image(data->mlx,
			"./tiles/floor.xpm", &img_width, &img_height);
	data->img_player = mlx_xpm_file_to_image(data->mlx,
			"./tiles/character.xpm", &img_width, &img_height);
	data->img_exit = mlx_xpm_file_to_image(data->mlx,
			"./tiles/exit.xpm", &img_width, &img_height);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx,
			"./tiles/collectible.xpm", &img_width, &img_height);
	if (!data->img_wall || !data->img_floor || !data->img_player
		|| !data->img_exit)
	{
		close_window(data);
		return (write(2, "Erreur : loading image failed\n", 31), 1);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2 || !is_valid_map_file(argv[1]))
		return (write(2, "Usage: ./so_long <map_file.ber>\n", 32), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Erreur : malloc failed\n", 23), 1);
	ft_memset(data, 0, sizeof(t_data));
	if (init_data(data, argv[1]) != 0)
	{
		free(data);
		return (1);
	}
	load_tiles(data);
	draw_map(data);
	data->collectible_nb = count_items(data, 'C');
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_loop(data->mlx);
}
