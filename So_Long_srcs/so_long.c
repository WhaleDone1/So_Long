/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:55:30 by bcarpent          #+#    #+#             */
/*   Updated: 2024/04/24 11:32:34 by bcarpent         ###   ########.fr       */
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

/*int	check_map_content(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == '1'
				|| map[i][j] == 'C' || map[i][j] == 'E'
				|| map[i][j] == 'P' || map[i][j] == '\n') //check for '\n' ?
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (1);
}
*/
int check_map_requirements(char **map, int C, int E, int P)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		printf("%c\n", map[i][j]);
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				C++;
			else if (map[i][j] == 'E')
				E++;
			else if (map[i][j] == 'P')
				P++;
			else if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] != '\n'))
			{
				printf("%d\n%d\n", map[i][j], j);
				return (-1);
			}
			j++;
		}
		i++;
	}
	printf("C = %d\nE = %d\nP = %d\n", C, E, P);
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
			printf("%d\n", j);
			return (-1);
		}
		else
		{
			while ((map[i][0] == '1') && (map[i][collumns - 1] == '1') && i < lines - 1)
				i++;
			if (i != lines - 1)
			{
				printf("%d\n", j);
				return (-1);
			}
			j = 0;
			while (map[i][j] == '1' && j < collumns - 1)
				j++;
			if (j != collumns - 1)
			{
				printf("%d\n", j);
				return (-1);
			}
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
		{
			printf("error map len");
			return (-1);
		}
		printf("%s", map[i]);
		i++;
	}
	close(fd);
	int t;
	int t2;
	t = check_map_borders(map, collumn_count, line_count);
	t2 = check_map_requirements(map, 0, 0, 0);

	if ((t == 1) && (t2 == 1))
	{
		printf("%d\n", t);
		printf("c'est good\n");
	}
	else
	{
		printf("%d\n%d\n", t, t2);
		printf("map error\n");
	}
	printf("nb line = %d\nnb colo = %d\n", line_count, collumn_count);
	free (map);
	return (line_count);
}
