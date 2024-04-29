/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:55:30 by bcarpent          #+#    #+#             */
/*   Updated: 2024/04/29 16:14:26 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../GNL/get_next_line.h"

void free_mlx(t_data *data)
{
	mlx_destroy_image(data->mlxptr, data->player.asset);
	mlx_destroy_image(data->mlxptr, data->collectible);
	mlx_destroy_image(data->mlxptr, data->exit);
	mlx_destroy_image(data->mlxptr, data->obstacle);
	mlx_destroy_image(data->mlxptr, data->ground);
	if (data->winptr)
		mlx_destroy_window(data->mlxptr, data->winptr);
	mlx_destroy_display(data->mlxptr);
	free(data->mlxptr);
}

void ft_error(t_data *data, char *s)
{
	int i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	free_mlx(data);
	write(2, s, ft_strlen(s));
	exit(1);
}
static int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int check_args(int argc, char **argv)
{
	int i;
	int n;
	char str[5];
	if (argc != 2)
		return (write(2, "Bad arguments\n", 14));
	i = ft_strlen(argv[1]) - 1;
	n = 3;
	while ((argv[1][i]) && (n >= 0))
	{
		str[n] = argv[1][i];
		n--;
		i--;
	}
	str[4] = '\0';
	if (ft_strcmp(str, ".ber") != 0)
		return (write(2, "Bad arguments\n", 14));
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	int fd;

	if (check_args(argc, argv) > 0)
		return (1);
	data.mlxptr = mlx_init();
	if (!data.mlxptr)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (1);
	init_asset(&data);
	init_map(&data, argv[1]);
	data.winptr = mlx_new_window(data.mlxptr, data.width * size, data.height * size, "bcarpent");
	if (!data.winptr)
		ft_error(&data, "Failed to create a new window");
	display_asset(&data);
	mlx_hook(data.winptr, 2, 1L << 0, &on_keypress, &data);
	mlx_hook(data.winptr, 17, 1L << 17, &on_destroy, &data);
	mlx_loop(data.mlxptr);
	return (0);
}
