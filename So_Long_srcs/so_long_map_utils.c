/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:03:48 by bcarpent          #+#    #+#             */
/*   Updated: 2024/05/06 11:58:39 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map(t_data *data, int collumn_count, int line_count)
{
	if ((check_map_borders(data->map, collumn_count, line_count)) != 1
		|| (check_map_requirements(data->map, 0, 0, data) != 1)
		|| (so_long_solver(data) != 1))
		return (-1);
	return (0);
}
