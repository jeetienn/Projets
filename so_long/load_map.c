/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:59:32 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 18:00:32 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_input(t_data *data, char *file_name)
{
	if (!data || !file_name)
	{
		ft_putstr_fd("Error: Invalid data or file name.\n", 2);
		return (-1);
	}
	return (0);
}

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Could not open file.\n", 2);
		return (-1);
	}
	return (fd);
}

int	allocate_map(t_data *data)
{
	int	i;

	i = 0;
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		ft_putstr_fd("Error: Memory allocation failed for map.\n", 2);
		return (-1);
	}
	while (i < data->map_height)
	{
		data->map[i] = NULL;
		i++;
	}
	data->map[data->map_height] = NULL;
	return (0);
}

int	count_lines(int fd)
{
	char	*line;
	int		count;

	line = get_next_line(fd);
	count = 0;
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	load_map(t_data *data, char *file_name)
{
	int	fd;

	if (validate_input(data, file_name) < 0)
		return (-1);
	data->map_height = get_map_height(file_name);
	if (data->map_height <= 0)
		return (-1);
	fd = open_file(file_name);
	if (fd < 0)
		return (-1);
	if (allocate_map(data) < 0)
	{
		close(fd);
		return (-1);
	}
	if (read_map_lines(data, fd) < 0)
		return (-1);
	close(fd);
	return (0);
}
