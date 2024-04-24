/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:56:09 by bcarpent          #+#    #+#             */
/*   Updated: 2024/04/24 16:01:37 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define size 24

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <../ml/mlx.h>

typedef struct t_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_data
{
	void	*mlxptr;
	void	*winptr;
	char	**map;
	void	*player;
	void	*ground;
	void	*obstacle;
	void	*collectible;
	void	*exit;
	int		height;
	int		width;
	int		moves;
}	t_data;

#endif
