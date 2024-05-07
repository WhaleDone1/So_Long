/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:03:48 by bcarpent          #+#    #+#             */
/*   Updated: 2024/05/07 09:25:36 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"

int	get_map(t_data *data, int collumn_count, int line_count)
{
	if ((check_map_borders(data->map, collumn_count, line_count)) != 1
		|| (check_map_requirements(data->map, 0, 0, data) != 1)
		|| (so_long_solver(data) != 1))
		return (-1);
	return (0);
}

void	show_exit(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (++y < data->width)
	{
		x = 0;
		while (++x < data->height)
			if (data->map[x][y] == 'E')
				mlx_put_image_to_window(data->mlxptr, data->winptr,
					data->exit, y * SIZE, x * SIZE);
	}
}

int	fd_error(t_data *data)
{
	mlx_destroy_display(data->mlxptr);
	free(data->mlxptr);
	write(2, "Cannot read\n", 12);
	return (1);
}
