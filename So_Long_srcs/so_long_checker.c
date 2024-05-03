/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:18:11 by bcarpent          #+#    #+#             */
/*   Updated: 2024/05/03 17:16:10 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"

static void ft_free_mapcpy(char **mapcpy)
{
    int    i;

    i = 0;
    while (mapcpy[i])
    {
        free(mapcpy[i]);
        i++;
    }
    if (mapcpy)
        free(mapcpy);
}

static char **mapdup(t_data *data)
{
    int i;
    char **mapcpy;

    i = 0;
    mapcpy = malloc(sizeof(char *) * (data->height + 1));
    if (!mapcpy)
        ft_error(data, "Malloc failed\n");
    mapcpy[0] = ft_strdup("");
    while (i < data->height)
    {
        mapcpy[i] = ft_strdup(data->map[i]);
        i++;
    }
    mapcpy[i] = '\0';
    return (mapcpy);
}

static void    flood_fill(char **mapcpy, int j, int i)
{
    if (mapcpy[i][j] == 'E')
        mapcpy[i][j] = '1';
    if (mapcpy[i][j] != '1' && mapcpy[i][j] != 'V')
    {
        mapcpy[i][j] = 'V';
        flood_fill(mapcpy, j + 1, i);
        flood_fill(mapcpy, j - 1, i);
        flood_fill(mapcpy, j, i + 1);
        flood_fill(mapcpy, j, i - 1);
    }
}

void    print_map(char **mapcpy)
{
    int i = 0;
    // int j = 0;
    while (mapcpy[i])
    {
        printf("%s", mapcpy[i]);
        i++;
    }
}

int so_long_solver(t_data *data)
{
    int i;
    int j;
    char **mapcpy;

    i = 0;
    mapcpy = mapdup(data);
    flood_fill(mapcpy, data->player.y, data->player.x);

    while (mapcpy[i])
    {
        j = 0;
        while (mapcpy[i][j])
        {
            if ((mapcpy[i][j] != '0') && (mapcpy[i][j] != '1')
            && (mapcpy[i][j] != '\n') && (mapcpy[i][j] != 'V'))
            {
                ft_free_mapcpy(mapcpy);
                return (-1);
            }
            j++;
        }
        i++;
    }
    ft_free_mapcpy(mapcpy);
    return (1);
}
