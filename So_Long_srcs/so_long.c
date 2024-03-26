/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:55:30 by bcarpent          #+#    #+#             */
/*   Updated: 2024/03/26 18:15:47 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"
//#include "../Libft/libft.h"
#include <stdio.h>//tmp

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

int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] != '0' || map[i][j] != '1'
				|| map[i][j] != 'C' || map[i][j] != 'E'
				|| map[i][j] != 'P') //check for '\n' ?
					return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char **map;
	int fd;
	int	line_count;
	int collumn_count;
	int	i;

	if (argc != 2)
		return (0);
	i = 0;
	collumn_count = 0;
	line_count = get_map_line_count(argv[1], &collumn_count, 0);
	map = malloc(sizeof(char *) * line_count + 1);
	fd = open(argv[1], O_RDONLY);
	while (i < line_count)
	{
		map[i] = get_next_line(fd);
		if ((int)ft_strlen(map[i]) - 1 != collumn_count)
			return (0);
		//printf("%s", map[i]);
		i++;
	}
	//printf("%d\n%d\n", line_count, collumn_count);
	//free map;
	return (line_count);
}
