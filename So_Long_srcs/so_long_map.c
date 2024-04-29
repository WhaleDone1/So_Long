/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:52:38 by barpent           #+#    #+#             */
/*   Updated: 2024/04/29 14:52:38 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"

static int init_player(t_data *data, int P, int x, int y)
{
    P++;
    data->player.x = x;
    data->player.y = y;
    return (P);
}

static int get_map_line_count(char *map, int *collumns, int fd)
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

static int check_map_requirements(char **map, int C, int E, int P, t_data *data)
{
    int i;
    int j;

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
                P = init_player(data, P, i, j);
            else if ((map[i][j] != '0') && (map[i][j] != '1') && (map[i][j] != '\n'))
                return (-1);
            j++;
        }
        i++;
    }
    if ((C > 0) && (P == 1) && (E == 1))
        return (1);
    return (0);
}
static int check_map_borders(char **map, int collumns, int lines)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (map[i])
    {
        while (map[0][j] == '1' && j < collumns)
            j++;
        if (j != collumns)
            return (-1);
        else
        {
            while ((map[i][0] == '1') && (map[i][collumns - 1] == '1') && i < lines - 1)
                i++;
            if (i != lines - 1)
                return (-1);
            j = 0;
            while (map[i][j] == '1' && j < collumns - 1)
                j++;
            if (j != collumns - 1)
                return (-1);
        }
        i++;
    }
    return (1);
}

void init_map(t_data *data, char *map)
{
    int i;
    int fd;
    int line_count;
    int collumn_count;

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
        i++;
    }
    data->width = collumn_count;
    data->height = line_count;
    close(fd);
    if ((check_map_borders(data->map, collumn_count, line_count)) != 1 || (check_map_requirements(data->map, 0, 0, 0, data) != 1))
        write(2, "map error\n", 10);
}