/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:52:38 by barpent           #+#    #+#             */
/*   Updated: 2024/05/06 12:07:00 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"

static int	init_player(t_data *data, int p, int x, int y)
{
	p++;
	data->player.x = x;
	data->player.y = y;
	return (p);
}

static int	get_map_line_count(char *map, int *collumns, int fd)
{
	int		line_count;
	int		read_count;
	int		count;
	char	*buffer;

	line_count = -1;
	read_count = 1;
	count = 0;
	buffer = malloc(sizeof(char) * 1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (read_count == 1)
	{
		read_count = read(fd, buffer, 1);
		if (buffer[0] == '\n')
		{
			line_count++;
			count = 1;
		}
		else if (count == 0)
			(*collumns)++;
	}
	return (free(buffer), close(fd), line_count);
}

int	check_map_requirements(char **map, int e, int p, t_data *data)
{
	int		i;
	int		j;
	int		c;

	i = -1;
	c = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'C')
				c++;
			else if (map[i][j] == 'E')
				e++;
			else if (map[i][j] == 'P')
				p = init_player(data, p, i, j);
			else if ((map[i][j] != '0') && (map[i][j] != '1')
			&& (map[i][j] != '\n'))
				return (-1);
		}
	}
	if ((c > 0) && (p == 1) && (e == 1))
		return (1);
	return (0);
}

int	check_map_borders(char **map, int collumns, int lines)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			if ((i == 0 || i == lines - 1 || j == 0 \
			|| j == collumns - 1) && map[i][j] != '1')
				return (-1);
		}
		if (j != collumns)
			return (-1);
	}
	return (1);
}

int	init_map(t_data *data, char *map)
{
	int		i;
	int		fd;
	int		line_count;
	int		collumn_count;

	i = 0;
	collumn_count = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_count = get_map_line_count(map, &collumn_count, 0);
	data->map = malloc(sizeof(char *) * (line_count + 1));
	while (i < line_count)
	{
		data->map[i] = get_next_line(fd);
		if ((int)ft_strlen(data->map[i]) - 1 != collumn_count)
			write(2, "map len error\n", 14);
		i++;
	}
	data->map[i] = 0;
	data->width = collumn_count;
	data->height = line_count;
	close(fd);
	return (get_map(data, collumn_count, line_count));
}
