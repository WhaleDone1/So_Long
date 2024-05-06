/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:52:32 by barpent           #+#    #+#             */
/*   Updated: 2024/05/06 12:15:15 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../Ft_Printf/ft_printf.h"

static int	stage_clear(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	on_destroy(t_data *data)
{
	int		i;

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

static void	move_player(t_data *data, int X, int Y)
{
	if (data->map[X][Y] != '1')
	{
		data->moves++;
		ft_printf("Move count: %d\n", data->moves);
		if (data->map[X][Y] == 'C')
			data->map[X][Y] = '0';
		mlx_put_image_to_window(data->mlxptr, data->winptr, data->ground,
			data->player.y * SIZE, data->player.x * SIZE);
		mlx_put_image_to_window(data->mlxptr, data->winptr, data->player.asset,
			Y * SIZE, X * SIZE);
		data->player.x = X;
		data->player.y = Y;
		if (data->map[X][Y] == 'E' && (stage_clear(data) == 1))
			on_destroy(data);
	}
	if (stage_clear(data) == 1)
		show_exit(data);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == 65307)
		on_destroy(data);
	else if (keysym == 119 || keysym == 65362)
		move_player(data, data->player.x - 1, data->player.y);
	else if (keysym == 115 || keysym == 65364)
		move_player(data, data->player.x + 1, data->player.y);
	else if (keysym == 97 || keysym == 65361)
		move_player(data, data->player.x, data->player.y - 1);
	else if (keysym == 100 || keysym == 65363)
		move_player(data, data->player.x, data->player.y + 1);
	(void)data;
	return (0);
}
