/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:56:09 by bcarpent          #+#    #+#             */
/*   Updated: 2024/05/07 09:22:01 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define SIZE 24

# include <sys/types.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <../ml/mlx.h>
# include <stdio.h>

typedef struct t_player
{
	int		x;
	int		y;
	void	*asset;
}	t_player;

typedef struct s_data
{
	void		*mlxptr;
	void		*winptr;
	char		**map;
	void		*ground;
	void		*obstacle;
	void		*collectible;
	void		*exit;
	int			height;
	int			width;
	int			moves;
	t_player	player;
}	t_data;

void	free_mlx(t_data *data);
void	ft_error(t_data *data, char *s);
void	init_asset(t_data *data);
void	display_asset(t_data *data);
void	show_exit(t_data *data);
int		on_destroy(t_data *data);
int		on_keypress(int keysym, t_data *data);
int		init_map(t_data *data, char *map);
int		check_map_requirements(char **map, int e, int p, t_data *data);
int		check_map_borders(char **map, int collumns, int lines);
int		so_long_solver(t_data *data);
int		get_map(t_data *data, int collumn_count, int line_count);
int		fd_error(t_data *data);

#endif
