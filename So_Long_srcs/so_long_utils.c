/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:52:32 by barpent           #+#    #+#             */
/*   Updated: 2024/04/29 14:52:32 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int stage_clear(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int on_destroy(t_data *data)
{
	int i;

	i = -1;
	if (data->map)
	{
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	free_mlx(data);
	exit(0);
	return (0);
}

static void move_player(t_data *data, int X, int Y)
{
	if (data->map[X][Y] != '1')
	{
		if (data->map[X][Y] == 'C')
			data->map[X][Y] = '0';
		mlx_put_image_to_window(data->mlxptr, data->winptr, data->ground, data->player.y * size, data->player.x * size);
		mlx_put_image_to_window(data->mlxptr, data->winptr, data->player.asset, Y * size, X * size);
		data->player.x = X;
		data->player.y = Y;
		if (data->map[X][Y] == 'E' && (stage_clear(data) == 1))
			on_destroy(data);
	}
	if (stage_clear(data) == 1)
	{
		Y = 0;
		while (++Y < data->width)
		{
			X = 0;
			while (++X < data->height)
				if (data->map[X][Y] == 'E')
					mlx_put_image_to_window(data->mlxptr, data->winptr, data->exit, Y * size, X * size);
		}
	}
}

int on_keypress(int keysym, t_data *data)
{
	if (keysym == 65307)
		on_destroy(data);
	else if (keysym == 122)
		move_player(data, data->player.x - 1, data->player.y);
	else if (keysym == 115)
		move_player(data, data->player.x + 1, data->player.y);
	else if (keysym == 113)
		move_player(data, data->player.x, data->player.y - 1);
	else if (keysym == 100)
		move_player(data, data->player.x, data->player.y + 1);
	(void)data;
	return (0);
}