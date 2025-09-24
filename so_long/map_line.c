/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:43:31 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:43:53 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_height(char *file_name)
{
	int	fd;
	int	height;

	fd = open_file(file_name);
	if (fd < 0)
		return (-1);
	height = count_lines(fd);
	close(fd);
	if (height <= 0)
	{
		ft_putstr_fd("Error: Invalid map height.\n", 2);
		return (-1);
	}
	return (height);
}

static int	process_line(t_data *data, char *line, int y)
{
	int		len;
	char	*clean_line;

	len = ft_strlen(line);
	if (line[len - 1] == '\n' || line[len - 1] == '\0')
		len--;
	clean_line = ft_substr(line, 0, len);
	if (!clean_line)
	{
		ft_putstr_fd("Error: Memory allocation failed.\n", 2);
		free(line);
		return (clean_exit(data, ""), -1);
	}
	if (y == 0)
		data->map_width = len;
	if (len != data->map_width)
	{
		ft_putstr_fd("Error: Map line width mismatch.\n", 2);
		free(clean_line);
		free(line);
		clean_exit(data, "");
		return (-1);
	}
	data->map[y] = clean_line;
	return (free(line), 0);
}

int	read_map_lines(t_data *data, int fd)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (y < data->map_height && (line != NULL))
	{
		if (process_line(data, line, y) < 0)
			return (close(fd), free(line), -1);
		y++;
		line = get_next_line(fd);
	}
	data->map[y] = NULL;
	if (y != data->map_height)
	{
		ft_putstr_fd("Error: Mismatch between lines.\n", 2);
		return (-1);
	}
	return (0);
}
