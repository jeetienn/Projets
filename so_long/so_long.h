/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:44:17 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:50:14 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include "lib/libft/libft.h"

# define KEY_ESC 65307
# define TILE_SIZE 64

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		pos_x;
	int		pos_y;
	int		move;
	int		last_tile;
	int		collectible_nb;

}	t_data;

int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);
int		init_data(t_data *data, char *map_file);
void	draw_map(t_data *data);
int		is_valid_map_file(char *filename);
int		clean_exit(t_data *data, char *error_msg);
int		load_map(t_data *data, char *file_name);
int		read_map_lines(t_data *data, int fd);
int		get_map_height(char *file_name);
int		count_lines(int fd);
int		open_file(char *file_name);
void	update_map(t_data *data, int new_x, int new_y);
void	init_player_pos(t_data *data);
int		count_items(t_data *data, char c);
int		is_true_map(t_data *data);
void	free_map_fill(char **map, int status);
int		is_walled(t_data *data);
int		is_rectangle(t_data *data);
void	draw_map(t_data *data);

#endif