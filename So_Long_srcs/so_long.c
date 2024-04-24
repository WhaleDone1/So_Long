/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:55:30 by bcarpent          #+#    #+#             */
/*   Updated: 2024/04/24 16:09:47 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"
//#include "../Libft/libft.h"
#include <stdio.h>//tmp

void	ft_error(t_data	*data, char *s)
{
	(void)data;
	write(2, s, ft_strlen(s));
	exit(1);
}

int	init_player(t_player *player, int P, int x, int y)
{	
	P++;
	player->x = x;
	player->y = y;
	return (P);
}

static int	get_map_line_count(char *map, int *collumns, int fd)
{
	int line_count;
	int read_count;
	int count;
	char *buffer;

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
	free(buffer);
	close(fd);
	return (line_count);
}

int check_map_requirements(char **map, int C, int E, int P, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				C++;
			else if (map[i][j] == 'E')
				E++;
			else if (map[i][j] == 'P')
				P = init_player(player, P, i, j);
			else if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] != '\n'))
			{
				return (-1);
			}
			j++;
		}
		i++;
	}
	if ((C > 0) && (P == 1) && (E == 1))
		return (1);
	return (0);
}
int	check_map_borders(char **map, int collumns, int lines)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (map[i])
	{
		while (map[0][j] == '1' && j < collumns)
			j++;
		if (j != collumns)
		{
			return (-1);
		}
		else
		{
			while ((map[i][0] == '1') && (map[i][collumns - 1] == '1') && i < lines - 1)
				i++;
			if (i != lines - 1)
			{
				return (-1);
			}
			j = 0;
			while (map[i][j] == '1' && j < collumns - 1)
				j++;
			if (j != collumns - 1)
			{
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

void	init_map(t_data *data, char *map, t_player *player)
{
	int	i;
	int	fd;
	int	line_count;
	int	collumn_count;
	
	i = 0;
	collumn_count = 0;
	line_count = get_map_line_count(map, &collumn_count, 0);
	data->map = malloc(sizeof(char *) * line_count + 1);
	fd = open(map, O_RDONLY);
	while (i < line_count)
	{
		data->map[i] = get_next_line(fd);
		if ((int)ft_strlen(data->map[i]) - 1 != collumn_count)
			write(2, "map len error\n", 14);
		//printf("%s", map[i]);
		i++;
	}
	data->width = collumn_count;
	data->height = line_count;
	close(fd);
	if ((check_map_borders(data->map, collumn_count, line_count)) != 1
		|| (check_map_requirements(data->map, 0, 0, 0, player) != 1)) // &player ?
		write(2, "map error\n", 10);
}

void	init_asset(t_data *data)
{
	int	width;
	int height;

	data->player = mlx_xpm_file_to_image(data->mlxptr,"/home/bcarpent/Documents/Projects/So_Long/Assets/player.xpm", &width, &height);
	if (!data->player)
		ft_error(data, "error xpm1");
	data->ground =  mlx_xpm_file_to_image(data->mlxptr,"/home/bcarpent/Documents/Projects/So_Long/Assets/grass.xpm", &width, &height);
	if (!data->ground)
		ft_error(data, "error xpm2");
	data->obstacle = mlx_xpm_file_to_image(data->mlxptr,"/home/bcarpent/Documents/Projects/So_Long/Assets/tree.xpm", &width, &height);
	if (!data->obstacle)
		ft_error(data, "error xpm3");
	data->collectible = mlx_xpm_file_to_image(data->mlxptr,"/home/bcarpent/Documents/Projects/So_Long/Assets/coin.xpm", &width, &height);
	if (!data->collectible)
		ft_error(data, "error xpm4");
	data->exit = mlx_xpm_file_to_image(data->mlxptr,"/home/bcarpent/Documents/Projects/So_Long/Assets/door.xpm", &width, &height);
	if (!data->exit)
		ft_error(data, "error xpm5");
}

void	display_asset(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->collectible  , j * size, i * size);
			else if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->exit  , j * size, i * size);
			else if (data->map[i][j] == '0')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->ground  , j * size, i * size);
			else if (data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->player  , j * size, i * size);
			else if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->obstacle  , j * size, i * size);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_player player;
	int fd;
	if (argc != 2)
		return (1);
	data.mlxptr = mlx_init();
	if (data.mlxptr == 0)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (1);
	init_asset(&data);
	init_map(&data, argv[1], &player); //&player ?
	data.winptr = mlx_new_window(data.mlxptr, data.width * size, data.height * size, "name");
	
	display_asset(&data);
	//free (map);
	mlx_loop(data.mlxptr);
	return (0);
}
