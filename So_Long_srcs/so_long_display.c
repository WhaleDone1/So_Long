/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:52:36 by barpent           #+#    #+#             */
/*   Updated: 2024/04/29 14:52:36 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_asset(t_data *data)
{
	int width;
	int height;

	data->player.asset = mlx_xpm_file_to_image(data->mlxptr, "Assets/player.xpm", &width, &height);
	if (!data->player.asset)
		ft_error(data, "error xpm1");
	data->ground = mlx_xpm_file_to_image(data->mlxptr, "Assets/grass.xpm", &width, &height);
	if (!data->ground)
		ft_error(data, "error xpm2");
	data->obstacle = mlx_xpm_file_to_image(data->mlxptr, "Assets/tree.xpm", &width, &height);
	if (!data->obstacle)
		ft_error(data, "error xpm3");
	data->collectible = mlx_xpm_file_to_image(data->mlxptr, "Assets/coin.xpm", &width, &height);
	if (!data->collectible)
		ft_error(data, "error xpm4");
	data->exit = mlx_xpm_file_to_image(data->mlxptr, "Assets/door.xpm", &width, &height);
	if (!data->exit)
		ft_error(data, "error xpm5");
}

void display_asset(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->collectible, j * size, i * size);
			else if (data->map[i][j] == '0' || data->map[i][j] == 'E' || data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->ground, j * size, i * size);
			else if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlxptr, data->winptr, data->obstacle, j * size, i * size);
		}
	}
	mlx_put_image_to_window(data->mlxptr, data->winptr, data->player.asset, data->player.y * size, data->player.x * size);
}