#include "so_long.h"

void	map_dup(char **map, char ***copy)
{
	int	i;
	int	height;

	height = 0;
	while (map[height])
		height++;
	*copy = malloc(sizeof(char *) * (height + 1));
	if (!*copy)
		return ;
	i = 0;
	while (map[i])
	{
		(*copy)[i] = ft_strdup(map[i]);
		if (!(*copy)[i])
		{
			free(copy);
			return ;
		}
		i++;
	}
	(*copy)[i] = NULL;
}

int	map_compare(char **map, char **copy)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == 'C' || map[y][x] == 'P' || map[y][x] == 'E')
				&& copy[y][x] != 'V')
			{
				ft_printf("Map compare failed\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	map_flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x]
		|| map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'D')
		return ;
	map[y][x] = 'V';
	map_flood_fill(map, y - 1, x);
	map_flood_fill(map, y + 1, x);
	map_flood_fill(map, y, x - 1);
	map_flood_fill(map, y, x + 1);
}

int	is_valid_path(t_data *data)
{
	char	**copy;
	int		result;

	map_dup(data->map, &copy);
	if (!copy)
		return (0);
	map_flood_fill(copy, data->pos_y, data->pos_x);
	result = map_compare(data->map, copy);
	free_map_fill(copy, 1);
	if (!result)
	{
		clean_exit(data, " ");
		return (0);
	}
	return (1);
}

int	is_true_map(t_data *data)
{
	if (!is_rectangle(data) || !is_walled(data))
	{
		ft_printf("The map must be rectangular and surrounded by walls.\n");
		return (0);
	}
	if (count_items(data, 'E') != 1 || count_items(data, 'P') != 1
		|| count_items(data, 'C') < 1)
	{
		ft_printf("The map must contain 1 ");
		ft_printf("character, 1 exit, and at least 1 collectible.\n");
		return (0);
	}
	data->collectible_nb = count_items(data, 'C');
	if (!is_valid_path(data))
	{
		ft_printf("The map's configuration makes it impossible to complete.\n");
		return (0);
	}
	return (1);
}
